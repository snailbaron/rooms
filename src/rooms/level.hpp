#pragma once

#include "cellar.hpp"
#include "geometry.hpp"

#include <istream>
#include <string_view>
#include <vector>

enum class Cell : unsigned char {
    Empty,
    Full,
    SmallColumn,
    LargeColumn,
};

class Level {
public:
    void loadFromString(std::string_view string);

    TraceResult<float> trace(
        const Point<float>& origin,
        Vector<float> lookDirection,
        Vector<float> rayDirection) const;

private:
    static constexpr float _cellSize = 1.f;
    static constexpr float _smallColumnRadius = 0.1f;
    static constexpr float _largeColumnRadius = 0.5f;

    Point<float> normalizedCellPoint(const Point<float>& levelPoint) const;
    Point<int> pointCell(const Point<float>& levelPoint) const;
    Point<float> cellCenter(size_t x, size_t y) const;

    Cellar<Cell> _cells;
};
