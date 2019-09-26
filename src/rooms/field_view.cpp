#include "field_view.hpp"

#include <algorithm>

FieldView::FieldView(const Field& field)
    : _field(field)
{ }

void FieldView::draw(SDL_Surface* surface)
{
    auto directionOrt = ort(_field.heroDirection);
    auto rayDirection = _field.heroDirection - directionOrt;
    for (int i = 0; i < _resolution.x; i++) {
        auto traceResult = _field.level.trace(
            _field.heroPosition, _field.heroDirection, rayDirection);

        auto height = static_cast<int>(
            _resolution.y / std::max(traceResult.distance, 1.f));
        auto offset = (_resolution.y - height) / 2;

        auto topLeft = globalPoint({i, offset});
        auto bottomRight = globalPoint({i + 1, _resolution.y - offset});
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
