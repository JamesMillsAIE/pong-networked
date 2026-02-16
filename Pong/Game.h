#pragma once

#include "Common.h"

#include <vector>

class Actor;
class GameBoard;
class Window;

using std::vector;

/**
 * The main control class of the game. Handles the window and actor memory.
 */
class Game
{
public:
	/**
	 * The function that changes the running variable.
	 * @see Game::m_isRunning
	 */
	static void Quit();

public:
	/**
	 * @param w The width of the screen
	 * @param h The height of the screen
	 * @param title The string shown in the title of the window
	 * @param clrColor The color used to clear the screen each frame
	 */
	Game(float w, float h, const int8* title, Color clrColor);
	~Game();

public:
	/**
	 * Runs the complete game loop; including Tick and Rendering.
	 * @return The success state of the Game Loop.
	 */
	int Run();

	/** Returns the max score required to win the game. */
	uint8 GetGoalScore() const;

private:
	static Game* m_instance; /**< The instance of the game. Used to prevent multiple games being created at once. */

private:
	Window* m_window; /**< The window instance of the game. */
	bool m_isRunning; /**< The variable to keep track of the open state of the game. */

	GameBoard* m_gameBoard; /**< Used to render the score and border / "net". */
	vector<Actor*> m_actors; /**< The collection of actors in the game. */

	uint8 m_goalScore; /**< The value used to determine the score to reach to win. */

private:
	/** The function used to create the actors and insert them into the actor list. */
	void ConstructActors();

	/** The initialisation function of the game. Used to initialise each actor and their default values. */
	void Initialise();

	/** The main update function of the game. Ticks each actor. */
	void Tick(float dt) const;

	/** The main render function of the game. Renders each actor. */
	void Render() const;

	/** The cleanup function of the game. Will automatically clean up the actors. */
	void Shutdown() const;

};