#include "game.hpp"

void Game::update(double delta)
{
    if (_field) {
        _field->update(delta);
    }
}
