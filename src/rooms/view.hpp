#pragma once

#include "field.hpp"
#include "field_view.hpp"
#include "widget.hpp"

#ifdef _WIN32
    #include <SDL.h>
#else
    #include <SDL2/SDL.h>
#endif

#include <memory>
#include <type_traits>

class View {
public:
    View(Field& field);

    bool isAlive() const;
    void processInput();
    void update(float delta);
    void draw();

private:
    template <class W>
    W& addWidget()
    {
        static_assert(std::is_base_of<Widget, W>());

        _widgets.push_back(std::make_unique<W>());
        return *static_cast<W*>(_widgets.back().get());
    }

    bool _isAlive = true;

    FieldView _fieldView;
    std::unique_ptr<SDL_Window, void(*)(SDL_Window*)> _window;

    std::vector<std::unique_ptr<Widget>> _widgets;
};
