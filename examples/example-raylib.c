#include <raylib.h>
#define TTWEENS_IMPLEMENTATION
#include "../tweens.h"

int main(void) {
    InitWindow(800, 500, "Tween example");
    SetTargetFPS(60);

    float x = 50.0f;

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_SPACE)) {
            TTweenFloat(&x, x < 400.0f ? 650.0f : 50.0f,
                (TTweenInfo) {
                    .duration = 0.8f,
                    .style = TT_EASE_QUINT,
                    .direction = TT_EASE_OUT
                }
            );
        }

        TTweenStep(GetFrameTime());

        BeginDrawing();
            ClearBackground((Color) {36, 36, 36, 255});

            DrawRectangle((int)x, 200, 100, 100, SKYBLUE);

            DrawText("Press SPACE to move the rectangle", 180, 100, 20, RAYWHITE);
            DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}