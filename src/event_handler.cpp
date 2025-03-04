#include <event_handler.h>

bool SingularityMouseLeftButtonPressed(Vector2 mousePosition,
                                       Singularity &singularity) {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
        CheckCollisionPointCircle(mousePosition,
                                  singularity.GetPosition(),
                                  singularity.GetRadius())) {
        return true;
    }
}
