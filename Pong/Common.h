#pragma once

#include <string>

#include <raylib/raylib.h>

using std::string;

typedef char int8;
typedef short int16;
typedef int int32;
typedef long int64;

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long uint64;

enum EExitResult : uint8
{
	InstanceNotNull = 2,
	WindowFailedToOpen
};