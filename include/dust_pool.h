#pragma once

#include <raylib.h>
#include <entity.h>
#include <array>

#define DUST_MIN 100

class Dust;

class DustPool {
  public:
    DustPool();

    void Init();

    Dust *GetDust(Vector2 position);

    void UpdateDraw(float deltaTime);

    void ToPool(int idx);

    void Reset();

    void CreateExplosion(Vector2 center, float radius);
  private:
    std::array<Dust, DUST_MIN> particles;
    std::array<bool, DUST_MIN> activeFlags;
    int activeCount;
};

extern DustPool dustPool;
