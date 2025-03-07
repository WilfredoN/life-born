#include <dust.h>
#include <dust_pool.h>
#include <math.h>

DustPool dustPool;

DustPool::DustPool() : activeCount(0) {
    Init();
}

void DustPool::Init() {
    for (int i = 0; i < DUST_MIN; i++) {
        particles[i] =
            Dust({0, 0}, DUST_MASS, DUST_SPEED, 10000.0f, WHITE, false);
        activeFlags[i] = false;
    }
    activeCount = 0;
}

Dust *DustPool::GetDust(Vector2 position) {
    for (int i = 0; i < DUST_MIN; i++) {
        if (!activeFlags[i]) {
            particles[i].SetPosition(position);
            particles[i].SetIsActive(true);
            activeFlags[i] = true;
            activeCount++;
            return &particles[i];
        }
    }
    return nullptr;
}

void DustPool::UpdateDraw(float deltaTime) {
    for (int i = 0; i < DUST_MIN; i++) {
        if (activeFlags[i]) {
            particles[i].Update(deltaTime);
            particles[i].Draw();
        }
    }
}

void DustPool::ToPool(int idx) {
    if (idx >= 0 && idx < DUST_MIN && activeFlags[idx]) {
        activeFlags[idx] = false;
        particles[idx].SetIsActive(false);
        activeCount--;
    }
}

void DustPool::Reset() {
    for (int i = 0; i < DUST_MIN; i++) {
        activeFlags[i] = false;
        particles[i].SetIsActive(false);
    }
    activeCount = 0;
}

void DustPool::CreateExplosion(Vector2 center, float radius) {
    for (int i = 0; i < DUST_MIN; i++) {
        float angle = GetRandomValue(0, 360) * DEG2RAD;
        float distance = GetRandomValue(0, (int)(radius * 0.8f));
        Vector2 position = {center.x + cosf(angle) * distance,
                            center.y + sinf(angle) * distance};

        Dust *dust = GetDust(position);
        if (dust) {
            Color color = WHITE;
            color.r = GetRandomValue(180, 250);
            color.g = GetRandomValue(180, 250);
            color.b = GetRandomValue(180, 250);
            dust->SetColor(color);

            Vector2 direction;
            float dx = position.x - center.x;
            float dy = position.y - center.y;

            float length = sqrtf(dx * dx + dy * dy);
            if (length > 0) {
                direction.x = dx / length;
                direction.y = dy / length;
            }
            else {
                angle = GetRandomValue(0, 360) * DEG2RAD;
                direction = {cosf(angle), sinf(angle)};
            }
            dust->SetDirection(direction);

            float speedFactor = 1.0f - (distance / radius);
            dust->SetInitialSpeed(DUST_SPEED * (0.5f + speedFactor));
            dust->SetSpeed(DUST_SPEED * (0.5f + speedFactor));

            dust->SetMass(DUST_MASS);
        }
    }
}
