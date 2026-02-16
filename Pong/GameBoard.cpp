#include "GameBoard.h"

#include <cassert>

#include "RaylibExt.h"
#include "Window.h"

float GameBoard::lineWidth = 10.f;
Color GameBoard::m_renderColor = LIGHTGRAY;
float GameBoard::m_fontSize = 50.f;

GameBoard::GameBoard(Window* window, const float scoreOffset, const float dashS, const int32 dashCount)
	: m_window{ window }, m_scoreOffset{ scoreOffset }, m_dashSpacing{ dashS }, m_dashCount{ dashCount }
{}

GameBoard::~GameBoard()
{
	m_window = nullptr;
}

void GameBoard::RenderBackground() const
{
	// Validate the window pointer and get the width / height of the screen
	assert(m_window != nullptr && L"Window is nullptr");
	const float w = m_window->Width();
	const float h = m_window->Height();

	// Render the top line of the board
	Rectangle rect = { .x = 0, .y = 0, .width = w, .height = lineWidth };
	DrawRectangleRec(rect, m_renderColor);

	// Render the bottom line of the board
	rect = { .x = 0.f, .y = h - lineWidth, .width = w, .height = lineWidth };
	DrawRectangleRec(rect, m_renderColor);

	// Calculate the length of a single dash
	const float dashLength = h / static_cast<float>(m_dashCount) - m_dashSpacing * .5f;

	// Set the default location and height of the dash
	rect.x = w * .5f - lineWidth * .5f;
	rect.width = lineWidth;
	rect.height = dashLength;

	// Render each dash in the correct location
	for (int32 i = 0; i < m_dashCount; ++i)
	{
		rect.y = static_cast<float>(i) * (dashLength + m_dashSpacing);
		DrawRectangleRec(rect, m_renderColor);
	}
}

void GameBoard::RenderScore(const uint32 score, const EHorizontalAlignment alignment) const
{
	// Validate the window pointer and get the screen width
	assert(m_window != nullptr && L"Window is nullptr");
	const float w = m_window->Width();

	// Count the amount of digits in the score
	const string scoreText = std::to_string(score);

	// Render the text to the correct side of the screen
	const float x = alignment == EHorizontalAlignment::Left ? m_scoreOffset : w - m_scoreOffset;
	DrawTextAligned(GetFontDefault(), scoreText.c_str(), { x, m_scoreOffset }, m_fontSize, 0.f, m_renderColor, alignment);
}
