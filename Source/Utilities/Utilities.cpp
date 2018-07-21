#include <cstring>

#include "../Debugging/Logger.h"
#include "Utilities.h"


namespace Utilities {
	
	void StripNewline(char* str)
	{
		char* newLine = strchr(str, '\n');
		if (newLine)
			*newLine = '\0';
	}
	
	BYTE* LoadImage(const char* fileName, unsigned int* width, unsigned int* height, unsigned int* bitDepth)
	{
		std::string msg("Image data from: ") ;
		// image format.
		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
		// pointer to the image, once loaded.
		FIBITMAP* dib{nullptr};
		// pointer to the image data.
		BYTE* bits{0};
		// check the file signature and deduce its format.
		fif = FreeImage_GetFileType(fileName, 0);
		std::cout << fif << std::endl;
		// if still unknown, try to guess the file format from the file extension.
		if (fif == FIF_UNKNOWN)
			fif = FreeImage_GetFIFFromFilename(fileName);
		// if still unkown, return failure.
		if (fif == FIF_UNKNOWN)
		{
			msg = "Unable to load: ";
			S3D_LOG("WARNING", msg + fileName);
			return nullptr;
		}
		// check that the plugin has reading capabilities and load the file.
		if (FreeImage_FIFSupportsReading(fif))
			dib = FreeImage_Load(fif, fileName);
		// if the image failed to load, return failure.
		if (!dib) 
		{
			S3D_LOG("WARNING", msg + fileName + " could not be loaded.");
			return nullptr;
		}
		
		// retrieve the image data.
		*bitDepth = FreeImage_GetBPP(dib); 
		bits = FreeImage_GetBits(dib);
		// get the image width and height.
		*width = FreeImage_GetWidth(dib);
		*height = FreeImage_GetHeight(dib);
		// if this somehow one of these failed (they shouldn't), return failure.
		if ((bits == 0) || (width == 0) || (height == 0)) 
		{
			S3D_LOG("WARNING", msg + fileName + " was null.");
			return nullptr;
		}
		FreeImage_Unload(dib);

		return bits;
	}

#ifdef DX12CONTEXT
	std::string GetLastErrorAsString()
	{
		//Get the error message, if any.
		DWORD errorMessageID = ::GetLastError();
		if (errorMessageID == 0)
			return std::string(); //No error message has been recorded

		LPSTR messageBuffer = nullptr;
		size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

		std::string message(messageBuffer, size);

		//Free the buffer.
		LocalFree(messageBuffer);

		return message;
	}
#endif
}