#pragma once

struct Color;

class GameBoard
{
public:
	static void RenderBackground(float w, float h, float lineW, float dashSpacing, int dashCount);
	static void RenderScore(float x, float y, unsigned int score, bool alignRight = false, float fontSize = 50);

private:
	static Color m_renderColor;

};