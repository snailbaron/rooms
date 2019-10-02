#include "level.hpp"

#include <cmath>
#include <fstream>
#include <limits>
#include <istream>
#include <sstream>
#include <stdexcept>

#include <iostream>

namespace {

Cellar<Cell> readCellsFromStream(std::istream& input)
{
    auto cells = Cellar<Cell>{};

    int x = 0;
    int y = 0;
    char c;
    for (input.get(c); input.good(); input.get(c)) {
        switch (c) {
            case '\n': x = 0; y++; break;

            case '#': cells(x, y) = Cell::Full;        x++; break;
            case 'o': cells(x, y) = Cell::SmallColumn; x++; break;
            case 'O': cells(x, y) = Cell::LargeColumn; x++; break;
            case '.': cells(x, y) = Cell::Empty;       x++; break;
            case '%': cells(x, y) = Cell::HalfHeight;  x++; break;
            case 'T': cells(x, y) = Cell::TallHeight;  x++; break;
            case ' ': break;

            default:
                std::cerr <<
                    "unknown map symbol interpreted as empty cell: " << c <<
                    "\n";
                cells(x, y) = Cell::Empty;
                x++;
                break;
        }
    }
    cells.inverseByY();

    return cells;
}

} // namespace

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

void Level::loadFromString(const std::string& string)
{
    auto stream = std::istringstream{string};
    _cells = readCellsFromStream(stream);
}

void Level::loadFromFile(const std::filesystem::path& filePath)
{
    auto stream = std::ifstream{filePath};
    if (!stream.is_open()) {
        throw std::runtime_error{
            "failed to open level file:" + filePath.string()};
    }
    _cells = readCellsFromStream(stream);
}

std::vector<Level::Hit> Level::trace(
    const Point& origin,
    Vector lookDirection,
    Vector rayDirection) const
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

    std::vector<Hit> hits;
    auto prevCellType = Cell::Empty;
    auto cellType = _cells.at(cell[0], cell[1]);
    for (;;) {
        size_t index = nextCellDistance[0] < nextCellDistance[1] ? 0 : 1;

        cell[index] += step[index];
        for (size_t i = 0; i < 2; i++) {
            if (cell[i] < 0 || cell[i] >= static_cast<int>(_cells.width())) {
                hits.push_back({
                    std::numeric_limits<float>::infinity(),
                    Vector{},
                    Cell::Empty});
                return hits;
            }
        }

        prevCellType = cellType;
        cellType = _cells.at(cell[0], cell[1]);

        if (prevCellType == Cell::HalfHeight) {
            hits.push_back({
                nextCellDistance[index] * dot(lookDirection, rayDirection),
                index == 0 ?
                    Vector{static_cast<float>(-step[0]), 0.f} :
                    Vector{0.f, static_cast<float>(-step[1])},
                Cell::Empty});
        }

        if (cellType == Cell::Full) {
            hits.push_back({
                nextCellDistance[index] * dot(lookDirection, rayDirection),
                index == 0 ?
                    Vector{static_cast<float>(-step[0]), 0.f} :
                    Vector{0.f, static_cast<float>(-step[1])},
                Cell::Full});
            return hits;
        } else if (cellType == Cell::HalfHeight ||
                cellType == Cell::TallHeight) {
            hits.push_back({
                nextCellDistance[index] * dot(lookDirection, rayDirection),
                index == 0 ?
                    Vector{static_cast<float>(-step[0]), 0.f} :
                    Vector{0.f, static_cast<float>(-step[1])},
                cellType});
        } else if (cellType == Cell::SmallColumn ||
                cellType == Cell::LargeColumn) {
            auto cellCenter = Point{
                cell[0] * _cellSize + 0.5f, cell[1] * _cellSize + 0.5f};
            auto traceResult = traceCircle(
                origin,
                rayDirection,
                cellCenter,
                _cells.at(cell[0], cell[1]) == Cell::SmallColumn ?
                    _smallColumnRadius : _largeColumnRadius);
            if (traceResult) {
                hits.push_back({
                    traceResult.distance * dot(lookDirection, rayDirection),
                    traceResult.normal,
                    cellType});
                return hits;
            }
        }

        nextCellDistance[index] += delta[index];
    }
}

Point Level::normalizedCellPoint(const Point& levelPoint) const
{
    return {
        std::fmod(levelPoint.x, _cellSize) / _cellSize,
        std::fmod(levelPoint.y, _cellSize) / _cellSize
    };
}

Point Level::cellCenter(size_t x, size_t y) const
{
    return {_cellSize * (x + 0.5f), _cellSize * (y + 0.5f)};
}
