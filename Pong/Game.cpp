#include "Game.h"

#include <cassert>

#include "Actor.h"
#include "GameBoard.h"
#include "RaylibExt.h"
#include "Window.h"

Game* Game::m_instance = nullptr;

void Game::Quit()
{
	// Validate the instance pointer and set running to false
	assert(m_instance != nullptr && L"Game Instance is nullptr");
	m_instance->m_isRunning = false;
}

Game::Game(const float w, const float h, const int8* title, const Color clrColor)
	: m_window{ new Window{ w, h, title, clrColor } }, m_isRunning{ true },
	m_gameBoard{ new GameBoard{ m_window, 15.f, 15.f, 10 } }
{}

Game::~Game()
{
	// Iterate over each actor and clean up the memory
	for (const Actor* actor : m_actors)
	{
		delete actor;
	}
	m_actors.clear();

	// Clean up the game board memory
	delete m_gameBoard;
	m_gameBoard = nullptr;

	// Clean up the window memory
	delete m_window;
	m_window = nullptr;
}

int Game::Run()
{
	// If the instance has already been set, return a fail code 
	if (m_instance != nullptr)
	{
		return InstanceNotNull;
	}

	// Make this instance the singleton instance
	m_instance = this;

	// Attempt to open the window, if it fails, return an error code
	if (!m_window->Open())
	{
		return WindowFailedToOpen;
	}

	// Run the initialisation code
	Initialise();

	while (m_isRunning)
	{
		Tick(GetFrameTime());

		// Render the screen, clearing it using the window system
		m_window->BeginFrame();
		Render();
		m_window->EndFrame();

		// If the window close request has been made, quit the game
		if (WindowShouldClose())
		{
			Quit();
		}
	}

	// Run the cleanup functionality and close the window.
	Shutdown();
	m_window->Close();

	// Reset the instance pointer and return success.
	m_instance = nullptr;
	return EXIT_SUCCESS;
}

void Game::ConstructActors()
{

}

void Game::Initialise()
{
	ConstructActors();

	// Iterate over each actor and run it's initialise function
	for (Actor* actor : m_actors)
	{
		actor->BeginPlay();
	}
}

void Game::Tick(const float dt) const
{
	// Tick each actor individually
	for (Actor* actor : m_actors)
	{
		actor->Tick(dt);
	}
}

void Game::Render() const
{
	// Render the Background
	m_gameBoard->RenderBackground();
	m_gameBoard->RenderScore(1, EHorizontalAlignment::Left);
	m_gameBoard->RenderScore(2, EHorizontalAlignment::Right);

	// Iterate over each actor and render it
	for (Actor* actor : m_actors)
	{
		actor->Render();
	}
}

void Game::Shutdown() const
{
	// Iterate over each actor and clean it up
	for (Actor* actor : m_actors)
	{
		actor->EndPlay();
	}
}
