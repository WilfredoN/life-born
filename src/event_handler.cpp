#include <event_handler.h>

bool SingularityMouseLeftButtonPressed(Vector2 mousePosition,
                                       Singularity &singularity) {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
        CheckCollisionPointCircle(mousePosition,
                                  singularity.GetPosition(),
                                  singularity.GetRadius())) {
        return true;
    }
    return false;
}

void SingularityResize(Singularity &singularity, float rotation) {
    float baseRadius = singularity.GetRadius();
    float amplitude = 0.1f;
    float newRadius = baseRadius + amplitude * sinf(rotation);

    singularity.SetRadius(newRadius);
}
