#pragma once

#if _DEBUG
#define DEBUG_FNC(NAME) \
	static void NAME##();
#define DEBUG_FNC_ONE_PARAM(NAME, PARAM_TYPE, PARAM_NAME) \
	static void NAME##(PARAM_TYPE PARAM_NAME##);
#else
#define DEBUG_FNC(NAME) \
	static void NAME##(){}
#define DEBUG_FNC_ONE_PARAM(NAME, PARAM_TYPE, PARAM_NAME) \
	static void NAME##(PARAM_TYPE PARAM_NAME##) {}
#endif

class Debug
{
public:
	static void Init();

public:
	DEBUG_FNC_ONE_PARAM(Log, const char*, message)
	DEBUG_FNC_ONE_PARAM(LogLine, const char*, message)

};