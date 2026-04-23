#include "raylib.h"

#include "game/Game.h"

int main() {
    const int tile = 16;
    const int scale = 3;
    const int ts = tile * scale;

    const int screenW = 20 * ts;
    const int screenH = 19 * ts + 90;

    InitWindow(screenW, screenH, "PixelGame");
    SetTargetFPS(60);

    Game g;
    g.rc.tilePx = ts;
    g.rc.screenW = screenW;
    g.rc.screenH = screenH;
    NewRun(g);

    while (!WindowShouldClose() && !g.requestQuit) {
        const int dtMs = static_cast<int>(GetFrameTime() * 1000.0f);
        Update(g, dtMs);

        BeginDrawing();
        Render(g);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

