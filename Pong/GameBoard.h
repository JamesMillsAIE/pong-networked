#pragma once

#include "Common.h"

enum class EHorizontalAlignment : uint8;

/**
 * The class that renders the edge borders, "net" and each score onto the screen.
 */
class GameBoard
{
public:
	/**
	 * @param window The reference to the window.
	 * @param scoreOffset How much the score is offset from each corner of the screen.
	 * @param dashS How far apart each dash on the "net" are.
	 * @param dashCount How many dashes are in the "net".
	 */
	GameBoard(class Window* window, float scoreOffset, float dashS, int32 dashCount);
	~GameBoard();

public:
	/** Renders the "net" on the screen. */
	void RenderBackground() const;
	/**
	 * Renders the score onto the screen.
	 * @param score The score to render to the screen.
	 * @param alignment EHorizontalAlignment::Left is player 1, EHorizontalAlignment::Right is player 2.
	 */
	void RenderScore(uint32 score, EHorizontalAlignment alignment) const;

private:
	static Color m_renderColor; /**< The color that the board and score render. */
	static float m_fontSize; /**< The font size that the score renders at. */
	static float m_lineWidth; /**< How thick the border and "net" are. */

private:
	class Window* m_window; /**< The reference to the window. Used to get the width and height of the screen. */
	float m_scoreOffset; /**< How much the score is offset from each corner of the screen. */

	float m_dashSpacing; /**< How far apart each space on the "net" are. */
	int32 m_dashCount; /**< How many dashes that are on the "net". */

};