#pragma once

#include "Actor.h"

#include <vector>

using std::vector;

class GameBoard;
class Player;
class Window;

/**
 * The class representing the ball. Handles collisions, velocity and rendering.
 */
class Ball : public Actor
{
public:
	float radius; /**< The size of the ball, this is used for rendering and collisions instead of the size variable. */

public:
	/**
	 * @param window The reference to the window to be used for screen calculations.
	 * @param paddles The list of paddles to check collisions against.
	 */
	Ball(Window* window, const vector<Player*>& paddles);

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

	/** Resets the ball to the center of the screen with the direction passed. */
	void Reset(Vector2 dir);

private:
	Window* m_window; /**< The reference to the window for size access. */

	Vector2 m_direction; /**< The direction the ball is moving in. */
	float m_moveSpeed; /**< How fast the ball moves in the direction every section. */

	vector<Player*> m_paddles; /**< The list of paddles to handle collisions. */

};