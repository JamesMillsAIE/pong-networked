// ReSharper disable CppClangTidyModernizeMacroToEnum
#include "pch.h"

#include <Core/Debug.h>
#include <Core/Game.h>

#include <Network/NetworkClient.h>
#include <Network/NetworkServer.h>

#define SCREEN_W 800
#define SCREEN_H 450
#define GAME_NAME "Pong"
#define CLR_COLOR BLACK

int main()
{
    // Initialise the debug system
    Debug::Init();

#ifndef SERVER
    INetwork* network = new NetworkClient;
#else
    INetwork* network = new NetworkServer;
#endif // !SERVER

    // Create the game instance with the correct network
    Game* game = new Game{ SCREEN_W, SCREEN_H, GAME_NAME, CLR_COLOR, network };

    // Try initialising the network and run the game if successful, storing the return state
    int returnState = network->Initialise();
    if (returnState == EXIT_SUCCESS)
    {
	    returnState = game->Run();
    }

    // Shutdown the network and clean up the memory
    network->Shutdown();
    delete game;
    delete network;

    // Return the state that was sent from the game
	return returnState;
}
