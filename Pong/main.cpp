#include <cstdlib>
#include <raylib/raylib.h>

#include "GameBoard.h"

int main()
{
    constexpr float screenWidth = 800;
    constexpr float screenHeight = 450;

    InitWindow(static_cast<int>(screenWidth), static_cast<int>(screenHeight), "raylib [core] example - basic window");

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        GameBoard::RenderBackground(screenWidth, screenHeight, 10.f, 15.f, 10);
        GameBoard::RenderScore(15.f, 15.f, 1);
        GameBoard::RenderScore(screenWidth - 15.f, 15.f, 1, true);

        EndDrawing();
    }

    CloseWindow();

	return EXIT_SUCCESS;
}
