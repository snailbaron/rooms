#include "level.hpp"

#include <cmath>
#include <fstream>
#include <limits>

namespace fs = std::filesystem;

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

void Level::loadFromStream(std::istream& input)
{
    size_t x = 0;
    size_t y = 0;
    char c;
    for (input.get(c); input.good(); input.get(c)) {
        if (c == '#') {
            _cells(x, y) = Cell::Full;
            x++;
        } else if (c == '\n') {
            x = 0;
            y++;
        }
    }

    _cells.inverseByY();
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
            if (c == '#') {
                _cells(x, y) = Cell::Full;
            }
            x++;
        }
    }
    _cells.inverseByY();
}

void Level::loadFromFile(const fs::path& path)
{
    auto stream = std::ifstream{path};
    loadFromStream(stream);
}

TraceResult Level::trace(
    const Point<float>& origin,
    Vector<float> lookDirection,
    Vector<float> rayDirection) const
{
    lookDirection.normalize();
    rayDirection.normalize();

    float dx = rayDirection.x == 0 ?
        std::numeric_limits<float>::infinity() : std::abs(1 / rayDirection.x);
    float dy = rayDirection.y == 0 ?
        std::numeric_limits<float>::infinity() : std::abs(1 / rayDirection.y);

    int stepX = sign(rayDirection.x);
    int stepY = sign(rayDirection.y);
    int cellX = static_cast<int>(origin.x);
    int cellY = static_cast<int>(origin.y);

    auto cellRelativeOrigin = normalizedCellPoint(origin);

    float nextXDistance = rayDirection.x > 0 ?
        dx * (1 - cellRelativeOrigin.x) : dx * cellRelativeOrigin.x;
    float nextYDistance = rayDirection.y > 0 ?
        dy * (1 - cellRelativeOrigin.y) : dy * cellRelativeOrigin.y;

    for (;;) {
        if (nextXDistance < nextYDistance) {
            cellX += stepX;
            if (_cells.at(cellX, cellY) == Cell::Full) {
                return {
                    nextXDistance * dot(lookDirection, rayDirection),
                    true
                };
            }
            nextXDistance += dx;
        } else {
            cellY += stepY;
            if (_cells.at(cellX, cellY) == Cell::Full) {
                return {
                    nextYDistance * dot(lookDirection, rayDirection),
                    false
                };
            }
            nextYDistance += dy;
        }

        if (cellX < 0 || cellX >= _cells.width() ||
                cellY < 0 || cellY >= _cells.height()) {
            return {std::numeric_limits<float>::infinity(), false};
        }
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
