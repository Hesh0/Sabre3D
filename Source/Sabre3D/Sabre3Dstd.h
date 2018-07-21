#pragma once

// Header with the standard includes and definitions used throughout the project.

#define WIN32_LEAN_AND_MEAN
#define _CRTDBG_MAP_ALLOCG_NEW
#include <stdlib.h>
#include <crtdbg.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <list>
#include <string>
#include <map>

#include "../Debugging/Logger.h"

//#define DX12CONTEXT
#define OPENGLCONTEXT

#if defined(DX12CONTEXT)
	#include <windows.h>
	#include <D3d12.h> 
#else
	#include <gl\glew.h>
#endif

const int USEOPENGL = 0x00;
const int USEDX12 = 0x01;

#define precision(precis) std::fixed << std::setprecision((precis))

#define benchmark_begin auto start_time = std::chrono::high_resolution_clock::now()

#define benchmark_end \
	do \
	{ \
		auto end_time = std::chrono::high_resolution_clock::now(); \
		auto time = end_time - start_time; \
		printf("%s took %f milliseconds to run\n", __FUNCTION__, std::chrono::duration_cast<std::chrono::milliseconds>(time).count()); \
	} \
	while(0)


// Might make SABRE3D multi-platform, so gotta keep that portability.
#ifdef _MSC_VER
	#define _arrlen(arr) _countof(arr) 
#else
	#define _arrlen(arr) sizeof arr / sizeof arr[0]
#endif


// Redefine new to get file and line number of each allocation.
#ifdef _DEBUG
	#ifndef DBG_NEW
		#define DBG_NEW new  (_NORMAL_BLOCK , __FILE__ , __LINE__)
	#endif
#else
	#define DBG_NEW new
#endif

