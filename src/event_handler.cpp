#include <event_handler.h>
#include <render.h>

static bool is_big_bang = false;
static bool is_pulse = true;
static float bang_timer = 0.0f;
static float dust_spawn_accumulator = 0.0f;
static const float PARTICLE_SPAWN_RATE = 100.0f;

void SpawnBangDust(const Singularity &singularity, int particleCount) {
    Vector2 center = singularity.GetPosition();
    float currentRadius = singularity.GetRadius();
    float spawnRadius = currentRadius * 0.9f;

    for (int i = 0; i < particleCount; i++) {
        float angle = GetRandomValue(0, 360) * DEG2RAD;
        Vector2 spawnPos = {center.x + cosf(angle) * spawnRadius,
                            center.y + sinf(angle) * spawnRadius};

        Dust *dust = dustPool.GetDust(spawnPos);
        if (dust) {
            Vector2 direction = {cosf(angle), sinf(angle)};
            dust->SetDirection(direction);
            dust->SetSpeed(DUST_SPEED * GetRandomValue(80, 120) / 100.0f);

            Color color = WHITE;
            color.r = GetRandomValue(180, 250);
            color.g = GetRandomValue(180, 250);
            color.b = GetRandomValue(180, 250);
            dust->SetColor(color);
        }
    }
}

bool IsBigBangActive() {
    return is_big_bang;
}

void TriggerBigBang(Singularity &singularity) {
    is_big_bang = true;
    is_pulse = false;
    bang_timer = 0.0f;
    dust_spawn_accumulator = 0.0f;
    printf("Big Bang!\n");
}

bool SingularityMouseLeftButtonPressed(Vector2 mousePosition,
                                       Singularity &singularity) {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
        CheckCollisionPointCircle(mousePosition,
                                  singularity.GetPosition(),
                                  singularity.GetRadius())) {
        TriggerBigBang(singularity);
        return true;
    }
    return false;
}

void SingularityResize(Singularity &singularity, float size) {
    if (is_pulse) {
        float baseRadius = singularity.GetRadius();
        float amplitude = 0.1f;
        float newRadius = baseRadius + amplitude * sinf(size);

        singularity.SetRadius(newRadius);
    }
}

void BigBangExplosion(Singularity &singularity, float deltaTime) {
    if (is_big_bang) {
        float newRadius;

        if (bang_timer < BANG_DURATION / 4) {
            float contractionRate = 5.0f * BANG_EFFECT;
            newRadius = singularity.GetRadius() - contractionRate * deltaTime;
            newRadius = fmaxf(newRadius, 5.0f);
        }
        else {
            float expansionRate = 5.0f * BANG_EFFECT;
            newRadius = singularity.GetRadius() + expansionRate * deltaTime;

            dust_spawn_accumulator += PARTICLE_SPAWN_RATE * deltaTime;
            int particlesToSpawn = static_cast<int>(dust_spawn_accumulator);
            if (particlesToSpawn > 0) {
                SpawnBangDust(singularity, particlesToSpawn);
                dust_spawn_accumulator -= particlesToSpawn;
            }
        }

        singularity.SetRadius(newRadius);
        float newOpacity = singularity.GetOpacity(singularity.GetColor()) -
                           (deltaTime / BANG_EFFECT);
        newOpacity = fmaxf(newOpacity, 0.0f);

        Color color = singularity.GetColor();
        singularity.setOpacity(color, newOpacity);
        singularity.SetColor(color);
        bang_timer += deltaTime;
        if (bang_timer >= BANG_DURATION) {
            is_big_bang = false;
            singularity.SetIsActive(false);
        }
    }
}
