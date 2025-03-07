#include <entity.h>
#include <event_handler.h>
#include <iostream>

Particle::Particle(Vector2 position,
                   float mass,
                   float speed,
                   float temperature,
                   Color color,
                   bool isActive) :
    position(position), mass(mass), speed(speed), temperature(temperature),
    color(color), isActive(isActive) {
}

void Particle::Update(float deltaTime) {
    (void)deltaTime;
}

void Particle::Draw() const {
    DrawRectangle(position.x, position.y, 5, 5, color);
}

Dust::Dust(Vector2 position,
           float mass,
           float speed,
           float temperature,
           Color color,
           bool isActive) :
    Particle(position, mass, speed, temperature, color, isActive) {
}

void Dust::Update(float deltaTime) {
    (void)deltaTime;
}

void Dust::Draw() const {
    DrawRectangle(position.x, position.y, 5, 5, color);
}

CelestialBody::CelestialBody(Vector2 position,
                             float mass,
                             float speed,
                             float temperature,
                             Color color,
                             bool isActive,
                             float radius,
                             float gravity) :
    Particle(position, mass, speed, temperature, color, isActive),
    radius(radius), gravity(gravity) {
}

void CelestialBody::Update(float deltaTime) {
    (void)deltaTime;
}

void CelestialBody::Draw() const {
    DrawCircle(position.x, position.y, radius, color);
}

Planet::Planet(Vector2 position,
               float mass,
               float speed,
               float temperature,
               Color color,
               bool isActive,
               float radius,
               float gravity,
               float atmosphere) :
    CelestialBody(position,
                  mass,
                  speed,
                  temperature,
                  color,
                  isActive,
                  radius,
                  gravity),
    atmosphere(atmosphere) {
}

void Planet::Update(float deltaTime) {
    (void)deltaTime;
}

void Planet::Draw() const {
    DrawCircle(position.x, position.y, GetRadius(), color);
}

Star::Star(Vector2 position,
           float mass,
           float speed,
           float temperature,
           Color color,
           bool isActive,
           float radius,
           float luminosity) :
    CelestialBody(position,
                  mass,
                  speed,
                  temperature,
                  color,
                  isActive,
                  radius,
                  0.0f),
    luminosity(luminosity) {
}

void Star::Update(float deltaTime) {
    (void)deltaTime;
}

void Star::Draw() const {
    DrawCircle(position.x, position.y, GetRadius(), color);
}

Singularity::Singularity(Vector2 position,
                         float mass,
                         float speed,
                         float temperature,
                         Color color,
                         bool isActive,
                         float radius,
                         float gravity,
                         float eventHorizonRadius,
                         float spin) :
    CelestialBody(position,
                  mass,
                  speed,
                  temperature,
                  color,
                  isActive,
                  radius,
                  gravity),
    eventHorizonRadius(eventHorizonRadius), spin(spin) {
}

void Singularity::Update(float deltaTime) {
    (void)deltaTime;
    float rotation = 0.0f;
    SingularityResize(*this, rotation);
}

void Singularity::Draw() const {
    DrawCircle(position.x, position.y, GetRadius(), color);
}
