#pragma once

#include "raylib/raylib.h"

// Horizontal alignment options
enum class EHorizontalAlignment : unsigned char
{
	Left,
	Center,
	Right
};

// Vertical alignment options
enum class EVerticalAlignment : unsigned char
{
	Top,
	Middle,
	Bottom
};

// Draw text with custom horizontal and vertical alignment
inline void DrawTextAligned(const char* text, const int x, const int y, const int fontSize, const Color color,
	const EHorizontalAlignment hAlign = EHorizontalAlignment::Left, const EVerticalAlignment vAlign = EVerticalAlignment::Top)
{
	const int textWidth = MeasureText(text, fontSize);
	const int textHeight = fontSize;  // Approximate height based on font size

	int drawX = x;
	int drawY = y;

	// Adjust horizontal position based on alignment
	switch (hAlign)
	{
		case EHorizontalAlignment::Left:
		{
			drawX = x;
			break;
		}
		case EHorizontalAlignment::Center:
		{
			drawX = x - textWidth / 2;
			break;
		}
		case EHorizontalAlignment::Right:
		{
			drawX = x - textWidth;
			break;
		}
	}

	// Adjust vertical position based on alignment
	switch (vAlign)
	{
		case EVerticalAlignment::Top:
		{
			drawY = y;
			break;
		}
		case EVerticalAlignment::Middle:
		{
			drawY = y - textHeight / 2;
			break;
		}
		case EVerticalAlignment::Bottom:
		{
			drawY = y - textHeight;
			break;
		}
	}

	DrawText(text, drawX, drawY, fontSize, color);
}

// Overload for using a custom Font
inline void DrawTextAligned(const Font& font, const char* text, const Vector2 position, const float fontSize,
	const float spacing, const Color color, const EHorizontalAlignment hAlign = EHorizontalAlignment::Left,
	const EVerticalAlignment vAlign = EVerticalAlignment::Top)
{
	auto [measuredX, measuredY] = MeasureTextEx(font, text, fontSize, spacing);

	Vector2 drawPos = position;

	// Adjust horizontal position based on alignment
	switch (hAlign)
	{
		case EHorizontalAlignment::Left:
			{
				drawPos.x = position.x;
				break;
			}
		case EHorizontalAlignment::Center:
			{
				drawPos.x = position.x - measuredX / 2;
				break;
			}
		case EHorizontalAlignment::Right:
			{
				drawPos.x = position.x - measuredX;
				break;
			}
	}

	// Adjust vertical position based on alignment
	switch (vAlign)
	{
		case EVerticalAlignment::Top:
			{
				drawPos.y = position.y;
				break;
			}
		case EVerticalAlignment::Middle:
			{
				drawPos.y = position.y - measuredY / 2;
				break;
			}
		case EVerticalAlignment::Bottom:
			{
				drawPos.y = position.y - measuredY;
				break;
			}
	}

	DrawTextEx(font, text, drawPos, fontSize, spacing, color);
}