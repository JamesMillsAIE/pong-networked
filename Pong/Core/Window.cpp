// ReSharper disable CppMemberFunctionMayBeStatic
#include "Core/Window.h"

#include <cstring>

float Window::Width() const
{
	return m_width;
}

float Window::Height() const
{
	return m_height;
}

Window::Window(const float w, const float h, const int8* title, const Color clrColor)
	: m_width{ w }, m_height{ h }, m_title{ nullptr }, m_clrColor{ clrColor }
{
	const size_t strLength = strlen(title);

	m_title = new int8[strLength + 1];
	strcpy_s(m_title, strLength + 1, title);
}

Window::~Window()
{
	delete[] m_title;
	m_title = nullptr;
}

bool Window::Open() const
{
	InitWindow(static_cast<int32>(m_width), static_cast<int32>(m_height), m_title);
	InitAudioDevice();

	return IsWindowReady();
}

void Window::Close() const
{
	CloseAudioDevice();
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
