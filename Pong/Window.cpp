// ReSharper disable CppMemberFunctionMayBeStatic
#include "Window.h"

#include <cstring>

float Window::Width() const
{
	return m_width;
}

float Window::Height() const
{
	return m_height;
}

Window::Window(const float w, const float h, const char* title, const Color clrColor)
	: m_width{ w }, m_height{ h }, m_title{ nullptr }, m_clrColor{ clrColor }
{
	const size_t strLength = strlen(title);

	m_title = new char[strLength + 1];
	strcpy_s(m_title, strLength + 1, title);
}

Window::~Window()
{
	delete[] m_title;
	m_title = nullptr;
}

bool Window::Open() const
{
	InitWindow(static_cast<int>(m_width), static_cast<int>(m_height), m_title);
	return IsWindowReady();
}

void Window::Close() const
{
	CloseWindow();
}

void Window::BeginFrame() const
{
	BeginDrawing();
	ClearBackground(m_clrColor);
}

void Window::EndFrame() const
{
	EndDrawing();
}
