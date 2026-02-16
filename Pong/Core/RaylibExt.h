#pragma once

#include <Core/Common.h>

/** Horizontal alignment options. */
enum class EHorizontalAlignment : uint8
{
	Left,
	Center,
	Right
};

/** Vertical alignment options. */
enum class EVerticalAlignment : uint8
{
	Top,
	Middle,
	Bottom
};

/**
 * Draw text with custom horizontal and vertical alignment
 * @param text The text to render to the screen.
 * @param x The horizontal position to place the text.
 * @param y The vertical position to place the text.
 * @param fontSize How large the text should be on the screen.
 * @param color The color the text should render.
 * @param hAlign The horizontal alignment of the text.
 * @param vAlign The vertical alignment of the text.
 */
inline void DrawTextAligned(const int8* text, const int32 x, const int32 y, const int32 fontSize, const Color color,
	const EHorizontalAlignment hAlign = EHorizontalAlignment::Left, const EVerticalAlignment vAlign = EVerticalAlignment::Top)
{
	const int32 textWidth = MeasureText(text, fontSize);
	const int32 textHeight = fontSize;  // Approximate height based on font size

	int32 drawX = x;
	int32 drawY = y;

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

/**
 * Draw text with custom horizontal and vertical alignment.
 * Overload for using a custom Font.
 * @param font The font used to render the text.
 * @param text The text to render to the screen.
 * @param position The location to place the text on the screen.
 * @param fontSize How large the text should be on the screen.
 * @param spacing How far apart each character is.
 * @param color The color the text should render.
 * @param hAlign The horizontal alignment of the text.
 * @param vAlign The vertical alignment of the text.
 */
inline void DrawTextAligned(const Font& font, const int8* text, const Vector2 position, const float fontSize,
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