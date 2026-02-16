// ReSharper disable CppClangTidyModernizeMacroToEnum
#include <Core/Debug.h>
#include <Core/Game.h>

#define SCREEN_W 800
#define SCREEN_H 450
#define GAME_NAME "Pong"
#define CLR_COLOR BLACK

int main()
{
    Debug::Init();

    Game* game = new Game{ SCREEN_W, SCREEN_H, GAME_NAME, CLR_COLOR };
    const int returnState = game->Run();
    
    delete game;
	return returnState;
}
