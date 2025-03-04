#include <event_handler.h>

static bool is_big_bang = false;
static bool is_pulse = true;
static float bang_timer = 0.0f;

bool SingularityMouseLeftButtonPressed(Vector2 mousePosition,
                                       Singularity &singularity) {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
        CheckCollisionPointCircle(mousePosition,
                                  singularity.GetPosition(),
                                  singularity.GetRadius())) {
        is_big_bang = true;
        is_pulse = false;
        bang_timer = 0.0f;
        printf("Big Bang!\n");
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
        float baseRadius = 50.0f;
        float newRadius;

        if (bang_timer < BANG_DURATION / 4) {
            float contractionRate = 5.0f * BANG_EFFECT;
            newRadius = singularity.GetRadius() - contractionRate * deltaTime;
            newRadius = fmaxf(newRadius, 5.0f);
        }
        else {
            float expansionRate = 5.0f * BANG_EFFECT;
            newRadius = singularity.GetRadius() + expansionRate * deltaTime;
        }

        singularity.SetRadius(newRadius);
        bang_timer += deltaTime;

        if (bang_timer >= BANG_DURATION) {
            is_big_bang = false;
            singularity.SetIsActive(false);
            // todo: spawn dust particles
        }
    }
}
