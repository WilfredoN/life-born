#include "raylib.h"
#include <entity.h>
#include <event_handler.h>
#include <render.h>

int main() {
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

    InitWindow(1280, 720, "Life Born");

    SetTargetFPS(180);

    Singularity singularity({640, 360},
                            1000.0f,
                            0.0f,
                            100.0f,
                            WHITE,
                            true,
                            50.0f,
                            10.0f,
                            75.0f,
                            0.5f);

    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();

        if (singularity.GetIsActive()) {
            renderSingularity(singularity);
        }

        BeginDrawing();
        ClearBackground(BLACK);

        if (singularity.GetIsActive()) {
            singularity.Draw();
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
