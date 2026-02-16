#include "Game.h"

#include <cassert>

#include "Actor.h"
#include "Ball.h"
#include "GameBoard.h"
#include "GoalZone.h"
#include "Player.h"
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
	m_gameBoard{ new GameBoard{ m_window, 15.f, 15.f, 10 } }, m_goalScore{ 5 }
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

uint8 Game::GetGoalScore() const
{
	return m_goalScore;
}

void Game::ConstructActors()
{
	Player* player1 = new Player{ EPlayerIndex::Player1, m_gameBoard, m_window };
	Player* player2 = new Player{ EPlayerIndex::Player2, m_gameBoard, m_window };

	Ball* ball = new Ball{ m_window, this, { player1, player2 } };

	GoalZone* gz1 = new GoalZone{ ball, player1, m_window };
	GoalZone* gz2 = new GoalZone{ ball, player2, m_window };

	m_actors.emplace_back(gz1);
	m_actors.emplace_back(gz2);

	m_actors.emplace_back(player1);
	m_actors.emplace_back(player2);

	m_actors.emplace_back(ball);
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
		if (actor->canTick)
		{
			actor->Tick(dt);
		}
	}
}

void Game::Render() const
{
	// Render the Background
	m_gameBoard->RenderBackground();

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
