#include <render.h>

static float size = 0.0f;

void renderSingularity(Singularity &singularity) {
    float deltaTime = GetFrameTime();
    Vector2 mousePosition = GetMousePosition();
    size += deltaTime * PULSE_SPEED;

    if (!SingularityMouseLeftButtonPressed(mousePosition, singularity)) {
        SingularityResize(singularity, size);
    }
    BigBangExplosion(singularity, deltaTime);
}
