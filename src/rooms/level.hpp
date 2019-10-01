#pragma once

#include "cellar.hpp"
#include "geometry.hpp"

#include <filesystem>
#include <istream>
#include <iterator>
#include <string>
#include <vector>

enum class Cell : unsigned char {
    Empty,
    Full,
    SmallColumn,
    LargeColumn,
    HalfHeight,
    TallHeight,
};

class Level {
public:
    struct Hit {
        float distance;
        Vector<float> normal;
        Cell cell;
    };

    void loadFromString(const std::string& string);
    void loadFromFile(const std::filesystem::path& filePath);

    std::vector<Hit> trace(
        const Point<float>& origin,
        Vector<float> lookDirection,
        Vector<float> rayDirection) const;

private:
    static constexpr float _cellSize = 1.f;
    static constexpr float _smallColumnRadius = 0.1f;
    static constexpr float _largeColumnRadius = 0.3f;

    Point<float> normalizedCellPoint(const Point<float>& levelPoint) const;
    Point<int> pointCell(const Point<float>& levelPoint) const;
    Point<float> cellCenter(size_t x, size_t y) const;

    Cellar<Cell> _cells;
};
