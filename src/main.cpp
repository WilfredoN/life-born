#include "raylib.h"
#include <entity.h>
#include <event_handler.h>

int main() {
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

    InitWindow(1280, 720, "Life Born");

    SetTargetFPS(180);

    Singularity singularity({640, 360},
                            1000.0f,
                            0.0f,
                            100.0f,
                            VIOLET,
                            50.0f,
                            10.0f,
                            75.0f,
                            0.5f);

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(BLACK);

        singularity.Update(GetFrameTime());
        singularity.Draw();

        Vector2 mousePosition = GetMousePosition();
        // Big Bang!
        if (SingularityMouseLeftButtonPressed(mousePosition, singularity)) {
            singularity.SetPosition(Vector2({0, 0}));
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
