#pragma once

#define WIN32_LEAN_AND_MEAN
#define _CRTDBG_MAP_ALLOCG_NEW
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <crtdbg.h>
#include <list>
#include <string>
#include <map>

#include "../Debugging/Logger.h"


// Redefine new to get file and line number of each allocation.
#ifdef _DEBUG
	#ifndef DBG_NEW
		#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
	#endif
#else
	#define DBG_NEW new
#endif
// Basically aheader with the standard includes and definitions used throughout the project
