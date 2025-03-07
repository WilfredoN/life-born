#pragma once

#define PULSE_SPEED 1.5f

#include "raylib.h"

class Particle {
  public:
    Particle(Vector2 position,
             float mass,
             float speed,
             float temperature,
             Color color,
             bool isActive);

    virtual ~Particle() = default;
    virtual void Update(float deltaTime);
    virtual void Draw() const;

    Vector2 GetPosition() const {
        return position;
    }
    float GetMass() const {
        return mass;
    }
    float GetSpeed() const {
        return speed;
    }
    float GetTemperature() const {
        return temperature;
    }
    Color GetColor() const {
        return color;
    }
    bool GetIsActive() const {
        return isActive;
    }

    float GetOpacity(Color color) const {
        return color.a;
    }

    void SetIsActive(bool newIsActive) {
        isActive = newIsActive;
    }

    void SetPosition(Vector2 newPosition) {
        position = newPosition;
    }
    void SetMass(float newMass) {
        mass = newMass;
    }
    void SetSpeed(float newSpeed) {
        speed = newSpeed;
    }
    void SetTemperature(float newTemperature) {
        temperature = newTemperature;
    }
    void SetColor(Color newColor) {
        color = newColor;
    }
    void setOpacity(Color &color, float newOpacity) {
        color.a = static_cast<unsigned char>(newOpacity);
    }
  protected:
    Vector2 position;
    float mass;
    float speed;
    float temperature;
    Color color;
    bool isActive;
};

class CelestialBody : public Particle {
  public:
    CelestialBody(Vector2 position,
                  float mass,
                  float speed,
                  float temperature,
                  Color color,
                  bool isActive,
                  float radius,
                  float gravity);

    void Update(float deltaTime) override;

    void Draw() const override;

    float GetGravity() const {
        return gravity;
    }
    void SetGravity(float newGravity) {
        gravity = newGravity;
    }
    float GetRadius() const {
        return radius;
    }

    void SetRadius(float newRadius) {
        radius = newRadius;
    }
  private:
    float radius;
    float gravity;
};

class Planet : public CelestialBody {
  public:
    Planet(Vector2 position,
           float mass,
           float speed,
           float temperature,
           Color color,
           bool isActive,
           float radius,
           float gravity,
           float atmosphere);

    void Update(float deltaTime) override;

    void Draw() const override;

    float GetAtmosphere() const {
        return atmosphere;
    }
    void SetAtmosphere(float newAtmosphere) {
        atmosphere = newAtmosphere;
    }
  private:
    float atmosphere;
};

class Star : public CelestialBody {
  public:
    Star(Vector2 position,
         float mass,
         float speed,
         float temperature,
         Color color,
         bool isActive,
         float radius,
         float luminosity);

    void Update(float deltaTime) override;

    void Draw() const override;

    float GetLuminosity() const {
        return luminosity;
    }
    void SetLuminosity(float newLuminosity) {
        luminosity = newLuminosity;
    }
  private:
    float luminosity;
};

class Singularity : public CelestialBody {
  public:
    Singularity(Vector2 position,
                float mass,
                float speed,
                float temperature,
                Color color,
                bool isActive,
                float radius,
                float gravity,
                float eventHorizonRadius,
                float spin);

    void Update(float deltaTime) override;

    void Draw() const override;

    void Big_Bang(Singularity &singularity);

    float GetEventHorizonRadius() const {
        return eventHorizonRadius;
    }
    void SetEventHorizonRadius(float newEventHorizonRadius) {
        eventHorizonRadius = newEventHorizonRadius;
    }
    float GetSpin() const {
        return spin;
    }
    void SetSpin(float newSpin) {
        spin = newSpin;
    }
  private:
    float eventHorizonRadius;
    float spin;
};
