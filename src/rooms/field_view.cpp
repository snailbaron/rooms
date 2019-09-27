#include "config.hpp"
#include "field_view.hpp"

#include <algorithm>

FieldView::FieldView(Field& field)
    : _field(field)
{
    _tasks.addTask(
        SwayTask{
            3,
            [this] (float value) {
                _headHeight = 10 * (value - 0.5f);
            }});
}

void FieldView::processInputEvent(const SDL_Event& event)
{
    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == config().moveForwardKey) {
            _field.heroControls.moveForward = true;
        } else if (event.key.keysym.sym == config().moveBackwardKey) {
            _field.heroControls.moveBackward = true;
        } else if (event.key.keysym.sym == config().moveLeftKey) {
            _field.heroControls.moveLeft = true;
        } else if (event.key.keysym.sym == config().moveRightKey) {
            _field.heroControls.moveRight = true;
        }
    } else if (event.type == SDL_KEYUP) {
        if (event.key.keysym.sym == config().moveForwardKey) {
            _field.heroControls.moveForward = false;
        } else if (event.key.keysym.sym == config().moveBackwardKey) {
            _field.heroControls.moveBackward = false;
        } else if (event.key.keysym.sym == config().moveLeftKey) {
            _field.heroControls.moveLeft = false;
        } else if (event.key.keysym.sym == config().moveRightKey) {
            _field.heroControls.moveRight = false;
        }
    } else if (event.type == SDL_MOUSEMOTION) {
        _field.heroControls.turnLeft -=
            event.motion.xrel * config().mouseSensitivity;
    }
}

void FieldView::update(float delta)
{
    _tasks.update(delta);
}

void FieldView::draw(SDL_Surface* surface)
{
    auto direction = _field.heroBody.rotation * Vector{0, 1};
    auto directionOrt = ort(direction);
    auto rayDirection = direction - directionOrt;
    for (int i = 0; i < _resolution.x; i++) {
        auto traceResult = _field.level.trace(
            _field.heroBody.position, direction, rayDirection);

        auto height = static_cast<int>(
            _resolution.y / std::max(traceResult.distance, 0.1f));
        auto offset = (_resolution.y - height) / 2;
        auto headCorrection = static_cast<int>(
            _headHeight / std::max(traceResult.distance, 1.f));

        auto topLeft = globalPoint({i, offset + headCorrection});
        auto bottomRight =
            globalPoint({i + 1, _resolution.y - offset + headCorrection});
        auto size = bottomRight - topLeft;

        auto rect = SDL_Rect{topLeft.x, topLeft.y, size.x, size.y};
        SDL_FillRect(
            surface,
            &rect,
            SDL_MapRGB(
                surface->format,
                50,
                traceResult.xWall ? 100 : 150,
                50));

        rayDirection += directionOrt * (2.f / _resolution.x);
    }
}

Point<int> FieldView::globalPoint(const Point<int>& localPoint) const
{
    return {
        _position.x + static_cast<int>(
            std::round(1.f * _size.x * localPoint.x / _resolution.x)),
        _position.y + static_cast<int>(
            std::round(1.f * _size.y * localPoint.y / _resolution.y))
    };
}
