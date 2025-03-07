#include <coordinates.h>

void wrap_coordinates(Vector2 &position) {
    if (position.x > GetScreenWidth()) {
        position.x = 0;
    }
    else if (position.x < 0) {
        position.x = GetScreenWidth();
    }

    if (position.y > GetScreenHeight()) {
        position.y = 0;
    }
    else if (position.y < 0) {
        position.y = GetScreenHeight();
    }
}
