#include "Ball.h"

#include <raylib/raymath.h>

#include "Game.h"
#include "GameBoard.h"
#include "Player.h"
#include "Window.h"

Ball::Ball(Window* window, Game* game, const vector<Player*>& paddles)
	: Actor{ Vector2Zeros, Vector2Zeros, 0.f, BLUE }, radius{ 5.f }, m_window{ window },
	m_game{ game }, m_direction{ Vector2Normalize({ 1.f, -1.f }) }, m_moveSpeed{ 100.f },
	m_players{ paddles }
{

}

void Ball::BeginPlay()
{
	// Start the ball in the center of the screen
	location =
	{
		.x = m_window->Width() * .5f,
		.y = m_window->Height() * .5f
	};
}

void Ball::Tick(float dt)
{
	location += m_direction * m_moveSpeed * dt;

	// Bounce off the top of the board
	if (location.y < GameBoard::lineWidth + radius)
	{
		m_direction.y *= -1.f;
	}

	// Bounce off the bottom of the board
	if (location.y > m_window->Height() - (GameBoard::lineWidth + radius))
	{
		m_direction.y *= -1.f;
	}

	// Check the collision against each paddle
	for (const Player* paddle : m_players)
	{
		if (CheckCollisionCircleRec(location, radius, paddle->Bounds()))
		{
			// Get the direction to the paddle
			const Vector2 paddleCenter = paddle->location + paddle->size * .5f;
			const Vector2 dirToPaddle = Vector2Normalize(paddleCenter - location);
			const float dot = fabsf(Vector2DotProduct(dirToPaddle, m_direction));

			// Calculate the normal based on the direction to the paddle
			Vector2 normal;
			if (dot >= 0.f && dot <= .5f)
			{
				normal =
				{
					.x = paddle->index == EPlayerIndex::Player1 ? -1.f : 1.f,
					.y = 0.f
				};
			}
			else
			{
				normal =
				{
					.x = 0.f,
					.y = paddle->index == EPlayerIndex::Player1 ? -1.f : 1.f
				};
			}

			// Reflect the velocity based on the calculated normal
			m_direction = Vector2Reflect(m_direction, normal);
		}
	}
}

void Ball::Render()
{
	DrawCircleV(location, radius, tint);
}

void Ball::Reset(const Vector2 dir)
{
	m_direction = dir;

	// Center the ball on the screen
	location =
	{
		.x = m_window->Width() * .5f,
		.y = m_window->Height() * .5f
	};

	for (const Player* player : m_players)
	{
		if (player->GetScore() >= m_game->GetGoalScore())
		{
			canTick = false;
		}
	}
}