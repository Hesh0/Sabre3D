#include "Utilities.h"



namespace Utilities {

	BYTE* LoadImage(const char* fileName, unsigned int* width, unsigned int* height, unsigned int* bitDepth)
	{
		// image format.
		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
		// pointer to the image, once loaded.
		FIBITMAP* dib{nullptr};
		// pointer to the image data.
		BYTE* bits{0};
		// check the file signature and deduce its format.
		fif = FreeImage_GetFileType(fileName, 0);
		// if still unknown, try to guess the file format from the file extension.
		if (fif == FIF_UNKNOWN)
			fif = FreeImage_GetFIFFromFilename(fileName);
		// if still unkown, return failure.
		if (fif == FIF_UNKNOWN)
			return nullptr;
		// check that the plugin has reading capabilities and load the file.
		if (FreeImage_FIFSupportsReading(fif))
			dib = FreeImage_Load(fif, fileName);
		// if the image failed to load, return failure.
		if (!dib)
			return nullptr;

		// retrieve the image data.
		*bitDepth = FreeImage_GetBPP(dib); 
		bits = FreeImage_GetBits(dib);
		// get the image width and height.
		*width = FreeImage_GetWidth(dib);
		*height = FreeImage_GetHeight(dib);
		// if this somehow one of these failed (they shouldn't), return failure.
		if ((bits == 0) || (width == 0) || (height == 0))
			return nullptr;
		FreeImage_Unload(dib);

		return bits;
	}
}