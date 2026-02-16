#pragma once

#if _DEBUG
#define DEBUG_FNC(NAME) (void (NAME)##();)
#else
#define DEBUG_FNC(NAME) (void (NAME)##(){})
#endif

class Debug
{
public:
	static void Init();

};