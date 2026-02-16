#include "Core/Debug.h"

#if _DEBUG
#include <crtdbg.h>
#endif

void Debug::Init()
{
#if _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
}
