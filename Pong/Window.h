#pragma once

#include "Common.h"

/**
 * A utility class to handle all window management functions inside Raylib.
 */
class Window
{
	friend class Game;

public:
	/** Returns the width value of the screen. */
	float Width() const;

	/** Returns the height value of the screen. */
	float Height() const;

private:
	float m_width; /**< The width of the display area. */
	float m_height; /**< The height of the display area. (This does not include the title bar.) */
	int8* m_title; /**< The title of the game shown in the title bar, this is memory managed by the class. */
	Color m_clrColor; /**< The color used to clear the screen each frame. */

private:
	/**
	 * @param w The horizontal size of the display area.
	 * @param h The vertical size of the display area.
	 * @param title The title to be shown in the window header.
	 * @param clrColor The color to be used to clear the screen each frame.
	 */
	Window(float w, float h, const int8* title, Color clrColor);
	~Window();

private:
	/**
	 * Attempts to initialise the window and sound system.
	 * @return Whether the window successfully opened.
	 */
	bool Open() const;

	/** Shuts down the window and sound system gracefully. */
	void Close() const;

	/** Begins the rendering loop of Raylib and clears the background with the Clear Color. */
	void BeginFrame() const;

	/** Finishes the rendering loop of Raylib, causing it to present. */
	void EndFrame() const;

};