#pragma once

#include "cellar.hpp"
#include "geometry.hpp"

#include <filesystem>
#include <istream>
#include <string_view>
#include <vector>

enum class Cell : bool {
    Empty = false,
    Full = true,
};

struct TraceResult {
    float distance;
    bool xWall;
};

class Level {
public:
    void loadFromStream(std::istream& input);
    void loadFromString(std::string_view string);
    void loadFromFile(const std::filesystem::path& path);

    TraceResult trace(
        const Point<float>& origin,
        Vector<float> lookDirection,
        Vector<float> rayDirection) const;

private:
    Point<float> normalizedCellPoint(const Point<float>& levelPoint) const;
    Point<int> pointCell(const Point<float>& levelPoint) const;

    static constexpr float _cellSize = 1.f;
    static constexpr size_t _width = 10;
    Cellar<Cell> _cells;
};
