#include "field.hpp"

namespace {

constexpr float ACCELERATION_FORCE = 100.f;
constexpr float DECELERATION_FORCE = 10.f;
constexpr float MAX_SPEED = 3.f;

} // namespace

void Body::update(float delta)
{
    position += velocity * delta;
}

void Field::update(float delta)
{
    if (heroControls.turnLeft != 0) {
        auto rotation = makeRotation(heroControls.turnLeft);
        heroBody.rotation *= rotation;
        heroControls.turnLeft = 0;
    }

    float moveRight = heroControls.moveRight - heroControls.moveLeft;
    float moveForward = heroControls.moveForward - heroControls.moveBackward;

    auto localForceDirection = normalized(Vector{moveRight, moveForward});
    auto forceDirection = heroBody.rotation * localForceDirection;

    auto acceleration = ACCELERATION_FORCE * forceDirection;
    auto deceleration = -DECELERATION_FORCE * heroBody.velocity;
    heroBody.velocity += (acceleration + deceleration) * delta;
    heroBody.velocity.clip(MAX_SPEED);
    heroBody.position += heroBody.velocity * delta;
}
