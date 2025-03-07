#pragma once

#include <raylib.h>
#include <entity.h>
#include <iostream>

enum DustMass
{
    DUST_SMALL = 1,
    DUST_MEDIUM = 5,
    DUST_LARGE = 10
};

class DustPool;
extern DustPool dustPool;

class Dust : public Particle {
  public:
    Dust() :
        Particle({0, 0}, 0.0f, 0.0f, 0.0f, WHITE, false), direction({0, 0}),
        initialSpeed(0.0f) {
    }
    Dust(Vector2 position,
         float mass,
         float speed,
         float temperature,
         Color color,
         bool isActive);

    void Update(float deltaTime) override;
    void Draw() const override;

    void SetDirection(Vector2 newDirection) {
        direction = newDirection;
    }
    Vector2 GetDirection() const {
        return direction;
    }
    void SetInitialSpeed(float newSpeed) {
        initialSpeed = newSpeed;
    }
    float GetInitialSpeed() const {
        return initialSpeed;
    }
  private:
    Vector2 direction;
    float initialSpeed;
};

#define DUST_MASS (rand() % 3 + 1.0f)
#define DUST_SPEED 500.0f
#define DUST_ROTATION_SPEED 0.5f
#define DUST_DECELERATION 0.5f

Dust CreateDust(Vector2 position);
