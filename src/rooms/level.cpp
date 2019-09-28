#include "level.hpp"

#include <cmath>
#include <fstream>
#include <limits>

int sign(float value)
{
    if (value > 0) {
        return 1;
    } else if (value < 0) {
        return -1;
    } else {
        return 0;
    }
}

void Level::loadFromString(std::string_view string)
{
    size_t x = 0;
    size_t y = 0;
    for (char c : string) {
        if (c == '\n') {
            x = 0;
            y++;
        } else {
            switch (c) {
                case '#': _cells(x, y) = Cell::Full; break;
                case 'o': _cells(x, y) = Cell::SmallColumn; break;
                case 'O': _cells(x, y) = Cell::LargeColumn; break;
                default: _cells(x, y) = Cell::Empty; break;
            }
            x++;
        }
    }
    _cells.inverseByY();
}

TraceResult<float> Level::trace(
    const Point<float>& origin,
    Vector<float> lookDirection,
    Vector<float> rayDirection) const
{
    lookDirection.normalize();
    rayDirection.normalize();

    float delta[2] = {
        rayDirection.x == 0 ?
            std::numeric_limits<float>::infinity() :
            std::abs(1 / rayDirection.x),
        rayDirection.y == 0 ?
            std::numeric_limits<float>::infinity() :
            std::abs(1 / rayDirection.y)
    };

    int step[2] = {sign(rayDirection.x), sign(rayDirection.y)};
    int cell[2] = {static_cast<int>(origin.x), static_cast<int>(origin.y)};

    auto cellRelativeOrigin = normalizedCellPoint(origin);

    float nextCellDistance[2] = {
        rayDirection.x > 0 ?
            delta[0] * (1 - cellRelativeOrigin.x) :
            delta[0] * cellRelativeOrigin.x,
        rayDirection.y > 0 ?
            delta[1] * (1 - cellRelativeOrigin.y) :
            delta[1] * cellRelativeOrigin.y
    };

    for (;;) {
        size_t index = nextCellDistance[0] < nextCellDistance[1] ? 0 : 1;

        cell[index] += step[index];
        for (size_t i = 0; i < 2; i++) {
            if (cell[i] < 0 || cell[i] >= static_cast<int>(_cells.width())) {
                return {std::numeric_limits<float>::infinity(), {}};
            }
        }

        if (_cells.at(cell[0], cell[1]) == Cell::Full) {
            return {
                nextCellDistance[index] * dot(lookDirection, rayDirection),
                index == 0 ?
                    Vector<float>{-step[0], 0.f} :
                    Vector<float>{0.f, -step[1]}
            };
        } else if (_cells.at(cell[0], cell[1]) == Cell::SmallColumn ||
                _cells.at(cell[0], cell[1]) == Cell::LargeColumn) {
            auto cellCenter = Point<float>{
                cell[0] * _cellSize + 0.5f, cell[1] * _cellSize + 0.5f};
            auto traceResult = traceCircle(
                origin,
                rayDirection,
                cellCenter,
                _cells.at(cell[0], cell[1]) == Cell::SmallColumn ?
                    _smallColumnRadius : _largeColumnRadius);
            if (traceResult) {
                return {
                    traceResult.distance * dot(lookDirection, rayDirection),
                    traceResult.normal
                };
            }
        }

        nextCellDistance[index] += delta[index];
    }
}

Point<float> Level::normalizedCellPoint(const Point<float>& levelPoint) const
{
    return {
        std::fmod(levelPoint.x, _cellSize) / _cellSize,
        std::fmod(levelPoint.y, _cellSize) / _cellSize
    };
}

Point<int> Level::pointCell(const Point<float>& levelPoint) const
{
    return {
        static_cast<int>(levelPoint.x),
        static_cast<int>(levelPoint.y)
    };
}

Point<float> Level::cellCenter(size_t x, size_t y) const
{
    return {_cellSize * (x + 0.5f), _cellSize * (y + 0.5f)};
}
