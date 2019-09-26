#pragma once

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
        if (x >= _width) {
            _width = x + 1;
        }
        if (y >= _height) {
            _height = y + 1;
        }

        auto i = index(x, y);
        if (_data.size() <= i) {
            _data.resize(i + 1);
        }
        return _data[i];
    }

    size_t width() const
    {
        return _width;
    }

    size_t height() const
    {
        return _height;
    }

    void inverseByX()
    {
        for (size_t i = 0; i < _width / 2; i++) {
            for (size_t j = 0; j < _height; j++) {
                std::swap((*this)(i, j), (*this)(_width - 1 - i, j));
            }
        }
    }

    void inverseByY()
    {
        for (size_t i = 0; i < _width; i++) {
            for (size_t j = 0; j < _height / 2; j++) {
                std::swap((*this)(i, j), (*this)(i, _height - 1 - j));
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
    size_t _height = 0;
};
