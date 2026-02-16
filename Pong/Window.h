#pragma once

#include <raylib/raylib.h>

class Window
{
	friend class Game;

public:
	float Width() const;
	float Height() const;

private:
	float m_width;
	float m_height;
	char* m_title;
	Color m_clrColor;

private:
	Window(float w, float h, const char* title, Color clrColor);
	~Window();

private:
	bool Open() const;
	void Close() const;

	void BeginFrame() const;
	void EndFrame() const;

};