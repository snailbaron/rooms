#pragma once

#include <algorithm>
#include <vector>

/**
 *  Y
 *
 *  ^
 *  |
 *  +----+----+----+----+
 *  | 10 | 12 | 14 | 15 |
 *  +----+----+----+----|
 *  |  5 |  7 |  8 | 13 |
 *  +----+----+----+----+
 *  |  2 |  3 |  6 | 11 |
 *  +----+----+----+----+
 *  |  0 |  1 |  4 |  9 |
 *  +----+----+----+----+-> X
 */

template <class T>
class Cellar {
public:
    const T& at(size_t x, size_t y) const
    {
        return _data.at(index(x, y));
    }

    T& operator()(size_t x, size_t y)
    {
        auto w = std::max(x, y) + 1;
        if (w * w >= _data.size()) {
            _width = w;
            _data.resize(w * w);
        }

        return _data[index(x, y)];
    }

    size_t width() const
    {
        return _width;
    }

    void inverseByX()
    {
        for (size_t i = 0; i < _width / 2; i++) {
            for (size_t j = 0; j < _width; j++) {
                std::swap((*this)(i, j), (*this)(_width - 1 - i, j));
            }
        }
    }

    void inverseByY()
    {
        for (size_t i = 0; i < _width; i++) {
            for (size_t j = 0; j < _width / 2; j++) {
                std::swap((*this)(i, j), (*this)(i, _width - 1 - j));
            }
        }
    }

private:
    size_t index(size_t x, size_t y) const
    {
        if (x >= y) {
            return x * x + y * 2;
        } else {
            return y * y + x * 2 + 1;
        }
    }

    std::vector<T> _data;
    size_t _width = 0;
};
