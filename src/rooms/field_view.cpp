#include "config.hpp"
#include "field_view.hpp"

#include <algorithm>

#include <iostream>

FieldView::FieldView(Field& field)
    : _field(field)
{
    _tasks.addTask(
        SwayTask{
            3,
            [this] (float value) {
                _headHeight = 100 * (value - 0.5f);
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
    auto rayDirection = direction - directionOrt * _horizontalFovRatio;
    for (int i = 0; i < _resolution.x; i++) {
        auto hits = _field.level.trace(
            _field.heroBody.position, direction, rayDirection);

        for (auto hitIterator = hits.rbegin(); hitIterator != hits.rend();
                ++hitIterator) {
            const auto& hit = *hitIterator;

            auto height = static_cast<int>(_resolution.y * _objectHeight /
                (2 * _verticalFovRatio * std::max(hit.distance, 0.1f)));
            auto offset = (_resolution.y - height) / 2;
            auto headCorrection = static_cast<int>(
                _headHeight /
                    (2 * _verticalFovRatio *
                        std::max(hit.distance, 1.f)));
            auto heightCorrection = 0;
            if (hit.cell == Cell::HalfHeight || hit.cell == Cell::Empty) {
                heightCorrection = static_cast<int>(height * 0.8f);
            } else if (hit.cell == Cell::TallHeight) {
                heightCorrection = static_cast<int>(height * 0.3f);
            }

            auto topLeft =
                globalPoint({i, offset + headCorrection + heightCorrection});
            auto bottomRight =
                globalPoint({i + 1, _resolution.y - offset + headCorrection});
            if (hit.cell == Cell::Empty) {
                bottomRight.y = _resolution.y;
            }
            auto size = bottomRight - topLeft;

            auto rect = SDL_Rect{topLeft.x, topLeft.y, size.x, size.y};
            auto brightness =
                std::abs(dot(hit.normal, Vector<float>{0, 1}));
            if (hit.cell == Cell::Empty) {
                brightness = -0.5f;
            }

            SDL_FillRect(
                surface,
                &rect,
                SDL_MapRGB(
                    surface->format,
                    90 + 50 * brightness,
                    100 + 50 * brightness,
                    80 + 50 * brightness));

            if (hit.cell == Cell::HalfHeight) {
                rect.y += rect.h;
                rect.h = _resolution.y - rect.y;
                SDL_FillRect(
                    surface,
                    &rect,
                    SDL_MapRGB(surface->format, 30, 30, 30));
            }
        }

        rayDirection += directionOrt *
            (2.f * _horizontalFovRatio / _resolution.x);
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
