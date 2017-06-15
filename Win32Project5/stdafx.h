// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
#include <windowsx.h>
#include <Commdlg.h>
#include <ObjIdl.h>
#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment(lib, "Gdiplus.lib")

// C RunTime Header Files
#define _USE_MATH_DEFINES
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <cmath>
#include <climits>


// TODO: reference additional headers your program requires here
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <sstream>

using std::endl;
using std::wstringstream;
using std::map;
using std::vector;
using std::wstring;