#include "game.hpp"

void Game::update(float delta)
{
    if (_field) {
        _field->update(delta);
    }
}
