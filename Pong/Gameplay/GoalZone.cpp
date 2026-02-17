#include "pch.h"

#include "Gameplay/GoalZone.h"

#include <Core/Window.h>

#include <Gameplay/Ball.h>
#include <Gameplay/Player.h>

#include <raylib/raymath.h>

constexpr float width = 10.f;

GoalZone::GoalZone(Ball* ball, Player* scorer, Window* window)
	: Actor{ Vector2Zeros, { width, window->Height() }, 0.f, { 255, 255, 255, 50 } },
	m_ball{ ball }, m_scorer{ scorer }, m_window{ window }
{}

void GoalZone::BeginPlay()
{
	location =
	{
		.x = m_scorer->index == EPlayerIndex::Player1 ? m_window->Width() - width : 0.f,
		.y = 0.f
	};
}

void GoalZone::Tick(float dt)
{
	if (CheckCollisionCircleRec(m_ball->location, m_ball->radius, Bounds()))
	{
		m_scorer->AddScore();

		m_ball->Reset(
		              Vector2Normalize(
		                               {
			                               .x = m_scorer->index == EPlayerIndex::Player1 ? 1.f : -1.f,
			                               .y = GetRandomValue(0, 1) == 0 ? -1.f : 1.f
		                               })
		             );
	}
}