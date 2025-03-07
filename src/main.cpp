#include "raylib.h"
#include <entity.h>
#include <event_handler.h>
#include <render.h>

// Simulation states
enum SimulationState
{
    SINGULARITY_STABLE,
    BIG_BANG_OCCURRING,
    UNIVERSE_EXPANDING
};

void Initialize(Singularity &singularity);
void Update(Singularity &singularity, float deltaTime, SimulationState &state);
void Render(const Singularity &singularity, SimulationState state);
void updateDust(float deltaTime);
bool IsBigBangTriggered();

int main() {
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
    srand(time(NULL));
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

    SimulationState state = SINGULARITY_STABLE;

    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();

        Update(singularity, deltaTime, state);
        Render(singularity, state);
    }

    CloseWindow();
    return 0;
}

void Update(Singularity &singularity, float deltaTime, SimulationState &state) {
    switch (state) {
        case SINGULARITY_STABLE:
            renderSingularity(singularity);

            if (IsBigBangTriggered()) {
                state = BIG_BANG_OCCURRING;
            }
            break;

        case BIG_BANG_OCCURRING:
            BigBangExplosion(singularity, deltaTime);
            updateDust(deltaTime);

            if (!singularity.GetIsActive()) {
                state = UNIVERSE_EXPANDING;
            }
            break;

        case UNIVERSE_EXPANDING:
            updateDust(deltaTime);
            break;
    }
}

void Render(const Singularity &singularity, SimulationState state) {
    BeginDrawing();
    ClearBackground(BLACK);

    switch (state) {
        case SINGULARITY_STABLE:
            if (singularity.GetIsActive()) {
                singularity.Draw();
            }
            break;

        case BIG_BANG_OCCURRING:
            if (singularity.GetIsActive()) {
                singularity.Draw();
            }
            renderDust();
            break;

        case UNIVERSE_EXPANDING:
            renderDust();
            break;
    }

    EndDrawing();
}

bool IsBigBangTriggered() {

    return IsBigBangActive();
}

void updateDust(float deltaTime) {
    dustPool.UpdateDraw(deltaTime);
}
