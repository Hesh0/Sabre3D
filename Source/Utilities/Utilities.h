#pragma once

#include <FreeImage.h>
#include <string>
#include <GL/glew.h>

namespace Utilities {
	void StripNewline(char* str);
	BYTE* LoadImage(const char* fileName, unsigned int* width, unsigned int* height, unsigned int* bitDepth);
}
