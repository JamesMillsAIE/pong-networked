#pragma once

#include <raylib/raylib.h>

class Window;

enum EExitResult : unsigned char
{
	InstanceNotNull = 2,
	WindowFailedToOpen
};

extern Window const* GetWindow();

class Game
{
	friend Window const* GetWindow();

public:
	static void Quit();

public:
	Game(float w, float h, const char* title, Color clrColor);
	~Game();

public:
	int Run();

private:
	static Game* m_instance;

private:
	Window* m_window;
	bool m_isRunning;

private:
	void BeginPlay();

	void Tick(float dt);
	void Render();

	void EndPlay();

};