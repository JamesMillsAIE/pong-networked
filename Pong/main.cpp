#include <cstdlib>
#include <raylib/raylib.h>

int main(int argC, char* argV[])
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawCircle(screenWidth / 2, screenHeight / 2, 25.f, RED);

        EndDrawing();
    }

    CloseWindow();

	return EXIT_SUCCESS;
}