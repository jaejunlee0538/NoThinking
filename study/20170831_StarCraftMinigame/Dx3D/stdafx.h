// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <functional>
#include <map>
#include <list>
#include <vector>
#include <assert.h>
#include <memory>
#include <string>

#include <d3d9.h>
#include <d3dx9.h>
#include <DxErr.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "DxErr.lib")
#pragma comment(lib, "legacy_stdio_definitions.lib")

#include "TimeManager.h"
#include "Logger.h"
#include "Math.h"
#include "HashStringID.h"
#define SINGLETON(classname)	\
private:\
classname() {}\
~classname() {}\
classname(const classname&){}\
public:\
static classname* GetInstance(){static classname instance; return &instance;}

#define SAFE_RELEASE(p) if(p){p->Release(); p = NULL;}
#define SAFE_RELEASE_ARR(pArr, count) \
					if(pArr){\
						for(int i=0;i<count;++i){\
							if (pArr[i]) {\
								pArr[i]->Release();\
								pArr[i] = NULL;\
							}\
						}\
					}

#define SAFE_DELETE(p) if(p){delete p; p = NULL;}
#define SAFE_DELETE_ARR(pArr) if(pArr){delete[] pArr; pArr = NULL;}
