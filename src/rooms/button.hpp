#pragma once

#include "widget.hpp"

#include <functional>

class Button : public Widget {
public:
    Button()
    {
    }

    void draw(sf::RenderWindow& window) override
    {
        window.draw(_rectangle, _transformable.getTransform());
        window.draw(_text, _transformable.getTransform());
    }

    bool contains(int x, int y) const override
    {
        const auto& position = _transformable.getPosition();
        const auto& size = _rectangle.getSize();
        return x >= position.x && x < position.x + size.x &&
            y >= position.y && y < position.y + size.y;
    }

    void onGetFocus() override
    {
        _hasFocus = true;
        recalculateColors();
    }

    void onLoseFocus() override
    {
        _hasFocus = false;
        recalculateColors();
    }

    void onPress() override
    {
        _isPressed = true;
        recalculateColors();
    }

    void onRelease() override
    {
        _isPressed = false;
        recalculateColors();
    }

    void onActivate() override
    {
        logging::debug() << "pressed button '" <<
            _text.getString().toAnsiString() << "'\n";
        _action();
    }

    Button& position(float x, float y)
    {
        _transformable.setPosition(x, y);
        return *this;
    }

    Button& size(float x, float y)
    {
        _rectangle.setSize({x, y});
        return *this;
    }

    Button& text(const std::string& text)
    {
        _text.setString(text);
        return *this;
    }

    Button& action(std::function<void()> action)
    {
        _action = std::move(action);
        return *this;
    }

private:
    void recalculateColors()
    {
        if (_isPressed) {
            if (_hasFocus) {
                _rectangle.setFillColor(sf::Color{250, 250, 100});
                _rectangle.setOutlineColor(sf::Color{80, 50, 50});
            } else {
                _rectangle.setFillColor(sf::Color{200, 200, 80});
                _rectangle.setOutlineColor(sf::Color{80, 50, 50});
            }
        } else {
            if (_hasFocus) {
                _rectangle.setFillColor(sf::Color{100, 250, 100});
                _rectangle.setOutlineColor(sf::Color{20, 20, 60});
            } else {
                _rectangle.setFillColor(sf::Color{100, 200, 100});
                _rectangle.setOutlineColor(sf::Color{0, 0, 0});
            }
        }
    }

    sf::Transformable _transformable;
    RoundedRectangleShape _rectangle{{120.f, 50.f}};
    sf::Font _font;
    sf::Text _text;
    std::function<void()> _action = []{};
    bool _hasFocus = false;
    bool _isPressed = false;
};
