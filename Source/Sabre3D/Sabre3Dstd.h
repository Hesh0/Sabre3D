#pragma once

// Header with the standard includes and definitions used throughout the project.

#define WIN32_LEAN_AND_MEAN
#define _CRTDBG_MAP_ALLOCG_NEW
#include <stdlib.h>
#include <crtdbg.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <map>

#include "../Debugging/Logger.h"

// Might make SABRE3D multi-platform, so gotta keep that portability.
#ifdef _MSC_VER
	#define _arrlen(arr) _countof(arr) 
#else
	#define_arrlen(arr) sizeof arr / sizeof arr[0]
#endif


// Redefine new to get file and line number of each allocation.
#ifdef _DEBUG
	#ifndef DBG_NEW
		#define DBG_NEW new  (_NORMAL_BLOCK , __FILE__ , __LINE__)
	#endif
#else
	#define DBG_NEW new
#endif

