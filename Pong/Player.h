#pragma once

#include "Actor.h"

enum class EPlayerIndex : uint8
{
	Player1,
	Player2
};

class GameBoard;
class Window;

/**
 * The class for the controllable paddles by the player.
 */
class Player : public Actor
{
public:
	EPlayerIndex index; /**< The index of the player, used for keybinds and colors / position. */

public:
	/**
	 * @param index The player index that is associated with this paddle.
	 * @param board The reference to the board for rendering score.
	 * @param window The reference to the window to be used for screen calculations.
	 */
	Player(EPlayerIndex index, GameBoard* board, Window* window);

public:
	/** The initialisation function of the actor. */
	void BeginPlay() override;

	/**
	 * The update function of the actor. Intended to be overridden.
	 * @param dt The frame time calculated by Raylib, passed down through the game.
	 */
	void Tick(float dt) override;

	/** The function where the actor can draw itself. */
	void Render() override;

	/** Adds a point to the score. */
	void AddScore();

	/** Gets the current score of the player. */
	uint8 GetScore() const;

private:
	GameBoard* m_gameBoard; /**< The reference to the window to be used for screen calculations. */
	Window* m_window; /**< The reference to the window for size access. */

	uint8 m_score; /**< The current score of the player. */
	float m_moveSpeed; /**< The speed that the paddle moves at. */

};