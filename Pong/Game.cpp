#include "Game.h"

#include <assert.h>
#include <cstdlib>

#include "GameBoard.h"
#include "Window.h"

Window const* GetWindow()
{
	assert(Game::m_instance != nullptr && L"Game Instance is nullptr");

	return Game::m_instance->m_window;
}

Game* Game::m_instance = nullptr;

void Game::Quit()
{
	assert(m_instance != nullptr && L"Game Instance is nullptr");

	m_instance->m_isRunning = false;
}

Game::Game(const float w, const float h, const char* title, const Color clrColor)
	: m_window{ new Window{ w, h, title, clrColor } }, m_isRunning{ true }
{
}

Game::~Game()
{
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

	BeginPlay();

	while (m_isRunning)
	{
		Tick(GetFrameTime());

		m_window->BeginFrame();
		Render();
		m_window->EndFrame();

		if (WindowShouldClose())
		{
			Quit();
		}
	}

	EndPlay();

	m_window->Close();

	return EXIT_SUCCESS;
}

void Game::BeginPlay()
{
}

void Game::Tick(float dt)
{
}

void Game::Render()
{
	GameBoard::RenderBackground(m_window->Width(), m_window->Height(), 10.f, 15.f, 10);
	GameBoard::RenderScore(15.f, 15.f, 1);
	GameBoard::RenderScore(m_window->Width() - 15.f, 15.f, 1, true);
}

void Game::EndPlay()
{
}
