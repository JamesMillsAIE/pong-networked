#include "Game.h"

#include <cassert>
#include <cstdlib>

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
	delete m_gameBoard;
	m_gameBoard = nullptr;

	delete m_window;
	m_window = nullptr;
}

int Game::Run()
{
	if (m_instance != nullptr)
	{
		return InstanceNotNull;
	}

	m_instance = this;

	if (!m_window->Open())
	{
		return WindowFailedToOpen;
	}

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

	Shutdown();

	m_window->Close();

	return EXIT_SUCCESS;
}

void Game::Initialise()
{}

void Game::Tick(float dt)
{}

void Game::Render()
{
	m_gameBoard->RenderBackground();

	m_gameBoard->RenderScore(1, EHorizontalAlignment::Left);
	m_gameBoard->RenderScore(2, EHorizontalAlignment::Right);
}

void Game::Shutdown()
{}
