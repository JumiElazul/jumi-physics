#include <raylib.h>

struct window_params {
    int width = 1920;
    int height = 1080;
    const char* title = "Jumi Physics";
};

int main() {
    window_params params;
    InitWindow(params.width, params.height, params.title);

    while (!WindowShouldClose()) {
        ClearBackground(RED);

        BeginDrawing();

        EndDrawing();
    }

    CloseWindow();
}
