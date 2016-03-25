#pragma once

#include <FreeImage.h>
#include <string>
#include <GL/glew.h>

namespace Utilities {
	 BYTE* LoadImage(const char* fileName, unsigned int* width, unsigned int* height, unsigned int* bitDepth);
}
