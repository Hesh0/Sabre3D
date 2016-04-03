#pragma once

#include "../Sabre3D/Sabre3Dstd.h"



//display flags
const unsigned char WRITE_TO_DEBUGGER = 0x01;
const unsigned char WRITE_TO_LOG_FILE = 0x02;

namespace Logger {
	
	class ErrorMessenger
	{
		bool m_ErrorIgnored;
	
	public:
		ErrorMessenger();
		~ErrorMessenger() {}
		void Show(const std::string& msg, bool isFatal, const char* funcName, const char* fileName, unsigned int lineNum);
	};
	
	bool RestartLogFile();
	void Init();
	void Destroy();
	void Log(const std::string& tag, const std::string& msg, const char* funcName, const char* fileName, unsigned int lineNum);
}

// Fatal error are well...bad and should always be reported.
#pragma region Debug Macro Definitions

#define S3D_FATAL(str) \
	do \
	{ \
		static Logger::ErrorMessenger* errorMessenger = DBG_NEW Logger::ErrorMessenger; \
		std::string s((str)); \
		errorMessenger->Show(s, true, __FUNCTION__, __FILE__, __LINE__); \
	} \
	while (0) 

#ifndef NDEBUG // debug is defined.

	#define S3D_ERROR(str) \
		do \
		{ \
			static Logger::ErrorMessenger* errorMessenger = DBG_NEW Logger::ErrorMessenger; \
			std::string s((str)); \
			errorMessenger->Show(s, false, __FUNCTION__, __FILE__, __LINE__); \
		} \
		while (0)
	
	#define S3D_WARNING(str) \
		do { \
			std::string s((str)); \
			Logger::Log("WARNING", s, __FUNCTION__, __FILE__, __LINE__); \
		} \
		while (0) 

	#define S3D_LOG(tag, str) \
		do \
		{ \
			std::string s((str)); \
			Logger::Log(tag, s, nullptr, nullptr, 0); \
		} \
		while (0)

	#define S3D_ASSERT(expr) \
		do \
		{ \
			if (!(expr)) \
			{ \
				static Logger::ErrorMessenger* errorMessenger = DBG_NEW Logger::ErrorMessenger; \
				std::string s("ASSERTION FAILED: "); \
				errorMessenger->Show(s, false, __FUNCTION__, __FILE__, __LINE__); \
			} \
		} while (0) 

	#define S3D_INFO(str) \
		do \
		{ \
			std::string s(#str); \
			Logger::Log("INFO", s, nullptr, nullptr, 0); \
		} \
		while(0) 

#else // release mode.

// define the macros in such a way that they are completely ignored by the compiler.

#define S3D_ERROR(str) do { (void)sizeof(str); } while(0) 
#define S3D_WARNING(str) do { (void)sizeof(str); } while(0) 
#define S3D_LOG(tag, str) do { (void)sizeof(tag); (void)sizeof(str); } while(0) 
#define S3D_ASSERT(expr) do { (void)sizeof(expr); } while(0) 
#define S3D_INFO(str) do { (void)sizeof(str); } while(0) 

#endif

#pragma endregion
	