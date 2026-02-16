#include "GoalZone.h"

#include <raylib/raymath.h>

#include "Ball.h"
#include "Player.h"
#include "Window.h"

constexpr float width = 10.f;

GoalZone::GoalZone(Ball* ball, Player* scorer, Window* window)
	: Actor{ Vector2Zeros, { width, window->Height() }, 0.f, { 255, 255, 255, 50 } },
	m_ball{ ball }, m_scorer{ scorer }, m_window{ window }
{}

void GoalZone::BeginPlay()
{
	location =
	{
		.x = (m_scorer->index == EPlayerIndex::Player1 ? 0.f : m_window->Width() - width),
		.y = 0.f
	};
}

void GoalZone::Tick(float dt)
{
	if (CheckCollisionCircleRec(m_ball->location, m_ball->radius, Bounds()))
	{
		m_scorer->AddScore();

		m_ball->Reset(
			Vector2Normalize({ .x = m_scorer->index == EPlayerIndex::Player1 ? -1.f : 1.f, .y = -1.f })
		);
	}
}

void GoalZone::Render()
{
	DrawRectangleRec(Bounds(), tint);
}
