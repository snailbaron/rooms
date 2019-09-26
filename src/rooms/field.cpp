#include "field.hpp"

namespace {

constexpr float ACCELERATION_FORCE = 1.f;
constexpr float DECELERATION_FORCE = 1.f;

} // namespace

void Body::update(float delta)
{
    position += velocity * delta;
}

void Field::update(float delta)
{
    auto localForceDirection =
        normalized(Vector{heroControls.moveRight, heroControls.moveForward});
    auto forceDirection = heroBody.rotation * localForceDirection;

    auto acceleration = ACCELERATION_FORCE * forceDirection;
    auto deceleration = -DECELERATION_FORCE * heroBody.velocity;
    heroBody.velocity += (acceleration + deceleration) * delta;
    heroBody.position += heroBody.velocity * delta;
}
