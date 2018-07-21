#pragma once

#include "../Sabre3D/Sabre3Dstd.h" // Linker error unless i include this first.
#include <FreeImage.h>
#include <string>
#include <GL/glew.h>

namespace Utilities {
	void StripNewline(char* str);
	BYTE* LoadImage(const char* fileName, unsigned int* width, unsigned int* height, unsigned int* bitDepth);
#ifdef DX12CONTEXT
	std::string GetLastErrorAsString();
#endif // DX12CONTEXT

}
