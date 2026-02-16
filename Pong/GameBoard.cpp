#include "GameBoard.h"

#include <cstdio>

#include <raylib/raylib.h>

#include "RaylibExt.h"

Color GameBoard::renderColor = LIGHTGRAY;

void GameBoard::RenderBackground(const float w, const float h, const float lineW, const float dashSpacing, const int dashCount)
{
	Rectangle rect = { 0, 0, w, lineW };
	DrawRectangleRec(rect, renderColor);

	rect = { .x = 0.f, .y = h - lineW, .width = w, .height = lineW };
	DrawRectangleRec(rect, renderColor);

	const float dashLength = h / static_cast<float>(dashCount) - dashSpacing * .5f;

	rect.x = w * .5f - lineW * .5f;
	rect.width = lineW;
	rect.height = dashLength;

	for (int i = 0; i < dashCount; ++i)
	{
		rect.y = static_cast<float>(i) * (dashLength + dashSpacing);
		DrawRectangleRec(rect, renderColor);
	}
}

void GameBoard::RenderScore(const float x, const float y, const unsigned int score, const bool alignRight, const float fontSize)
{
	if (score >= 10)
	{
		return;
	}

	char text[2];
	if (sprintf_s(text, 2, "%d", score) == -1)
	{
		return;
	}

	const Font font = GetFontDefault();
	DrawTextAligned(font, text, { x, y }, fontSize, 0.f, renderColor, alignRight ? EHorizontalAlignment::Right : EHorizontalAlignment::Left);
}