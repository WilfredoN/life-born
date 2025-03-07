#include <dust.h>
#include <dust_pool.h>
#include <math.h>
#include <coordinates.h>

Dust::Dust(Vector2 position,
           float mass,
           float speed,
           float temperature,
           Color color,
           bool isActive) :
    Particle(position, mass, speed, temperature, color, isActive),
    direction({0, 0}), initialSpeed(0.0f) {
}

void Dust::Update(float deltaTime) {
    if (!isActive)
        return;

    position.x += direction.x * speed * deltaTime;
    position.y += direction.y * speed * deltaTime;

    float randomFactor = 0.1f;

    position.x += (GetRandomValue(-10, 10) / 10.0f) * randomFactor * deltaTime;
    position.y += (GetRandomValue(-10, 10) / 10.0f) * randomFactor * deltaTime;
    wrap_coordinates(position);
    speed = fmaxf(speed - DUST_DECELERATION * deltaTime, 50.0f);
}

void Dust::Draw() const {
    if (isActive) {
        DrawRectangle(position.x, position.y, 5, 5, color);
    }
}

Dust CreateDust(Vector2 position) {
    return Dust(position, DUST_MASS, DUST_SPEED, 10000.0f, WHITE, true);
}
