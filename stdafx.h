// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once
//uilib 相关配置
// #include "UIlib.h"
// #ifdef _DEBUG
// #       pragma comment(lib, "../Common/lib/UiLib_d.lib")
// #else
// #       pragma comment(lib, "../Common/lib/UiLib_u.lib")
// #endif

//duilib 相关配置
#include <UIlib.h>
using namespace DuiLib;
#ifdef _DEBUG
#	ifdef _UNICODE
#		pragma comment(lib,"DuiLib_ud.lib")
#	else
#      pragma comment(lib,"Duilib_d.lib")
#	endif
#else
#	ifdef _UNICODE
#		pragma comment(lib,"Duilib_u.lib")
#	else
#		pragma comment(lib,"Duilib.lib")
#	endif
#endif

#include "Resource.h"

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: reference additional headers your program requires here
