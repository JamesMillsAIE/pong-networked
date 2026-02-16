#include "Core/Debug.h"

#include <iostream>

#if _DEBUG
#include <crtdbg.h>
#endif

void Debug::Init()
{
#if _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
}

#if _DEBUG
void Debug::Log(const char* message)
{
	std::cout << message;
}

void Debug::LogLine(const char* message)
{
	std::cout << message << "\n";
}
#endif