#pragma once

#include "Actor.h"

class Ball;
class Player;
class Window;

class GoalZone : public Actor
{
public:
	/**
	 * @param ball The ball to check the against the goal.
	 * @param scorer The player that will receive a point when a goal is scored.
	 * @param window The reference to the window to be used for screen calculations.
	 */
	GoalZone(Ball* ball, Player* scorer, Window* window);

public:
	/** The initialisation function of the actor. */
	void BeginPlay() override;

	/**
	 * The update function of the actor. Intended to be overridden.
	 * @param dt The frame time calculated by Raylib, passed down through the game.
	 */
	void Tick(float dt) override;

private:
	Ball* m_ball; /**< The reference to the ball. */
	Player* m_scorer; /**< The player that will receive a point when a goal is scored. */
	Window* m_window; /**< The reference to the window for size access. */

};