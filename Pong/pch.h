// pch.h
#pragma once

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define NOUSER           // Prevents winuser.h - this is the key fix!
#define NOGDI            // Prevents wingdi.h
#define _WINSOCKAPI_     // Prevents old winsock.h

// Include raylib FIRST
#include <raylib/raylib.h>

// Now Windows networking headers (won't include winuser.h due to NOUSER)
#include <winsock2.h>
#include <ws2tcpip.h>

// Now enet
#include <enet/enet.h>