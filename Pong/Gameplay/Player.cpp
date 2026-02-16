#include "Gameplay/Player.h"

#include <Core/RaylibExt.h>
#include <Core/Window.h>

#include <Gameplay/GameBoard.h>

#include <raylib/raymath.h>

constexpr float width = 15.f;
constexpr float height = 100.f;
constexpr float startOffset = 20.f;

Player::Player(const EPlayerIndex index, GameBoard* board, Window* window)
	: Actor{ {}, Vector2{ width, height }, 0.f, RED }, index{ index }, m_gameBoard{ board }, m_window{ window },
	m_score{ 0 }, m_moveSpeed{ 150.f }
{

}

void Player::BeginPlay()
{
	// Move the player to the center of their respective sides.
	location =
	{
		.x = (index == EPlayerIndex::Player1 ? startOffset : m_window->Width() - (size.x + startOffset)),
		.y = m_window->Height() * .5f - size.y * .5f
	};
}

void Player::Tick(const float dt)
{
	// Cache the keybinds based on the player index.
	const KeyboardKey upKey = index == EPlayerIndex::Player1 ? KEY_W : KEY_UP;
	const KeyboardKey downKey = index == EPlayerIndex::Player1 ? KEY_S : KEY_DOWN;

	// Update the player position with input and confine to the game border.
	location.y += m_moveSpeed * dt * (static_cast<float>(IsKeyDown(downKey)) - static_cast<float>(IsKeyDown(upKey)));
	location.y = fmaxf(fminf(location.y, m_window->Height() - size.y - GameBoard::lineWidth), GameBoard::lineWidth);
}

void Player::Render()
{
	// Render the paddle rectangle and the score for this player
	DrawRectanglePro(Bounds(), Vector2Zeros, rotation, tint);
	m_gameBoard->RenderScore(m_score, index == EPlayerIndex::Player1 ? EHorizontalAlignment::Left : EHorizontalAlignment::Right);
}

void Player::AddScore()
{
	m_score++;
}

uint8 Player::GetScore() const
{
	return m_score;
}
