#include <Windows.h>
#include <cstring>

#include "Logger.h"

#pragma region Constants and Globals

#define LOG_FILE "Sabre3D.log"

// display flags.
#ifndef NDEBUG
	const unsigned char ERROR_FLAG_DEFAULT = (WRITE_TO_DEBUGGER | WRITE_TO_LOG_FILE);
	const unsigned char WARNING_FLAG_DEFAULT = (WRITE_TO_DEBUGGER | WRITE_TO_LOG_FILE);
	const unsigned char LOG_FLAG_DEFAULT = (WRITE_TO_DEBUGGER | WRITE_TO_LOG_FILE);

#elif NDEBUG
	const unsigned char ERROR_FLAG_DEFAULT = (WRITE_TO_LOG_FILE);
	const unsigned char WARNING_FLAG_DEFAULT = (WRITE_TO_LOG_FILE);
	const unsigned char LOG_FLAG_DEFAULT = (WRITE_TO_LOG_FILE);

#else
	const unsigned char ERROR_FLAG_DEFAULT = 0x0;
	const unsigned char WARNING_FLAG_DEFAULT = 0x0;
	const unsigned char LOG_FLAG_DEFAULT = 0x0;

#endif

// singleton
class LogManager;
static LogManager* s_pLogManager{nullptr};

#pragma endregion


#pragma region LogManager Class

class LogManager
{
	typedef std::map<std::string, unsigned char> Tags;
	typedef std::list<Logger::ErrorMessenger*> ErrorMessengerList;

	Tags m_Tags;
	ErrorMessengerList m_errorMessengers;

public:
	enum ErrorDialogResult
	{
		ERROR_ABORT,
		ERROR_RETRY_,
		ERROR_IGNORE
	};

public:
	LogManager();
	~LogManager();
	void SetDisplayFlags(const std::string& tag, unsigned char flag);
	void Log(const std::string& tag, const std::string& msg, const char* funcName, const char* fileName, unsigned int lineNum);
	void AddErrorMessenger(Logger::ErrorMessenger* messenger);
	ErrorDialogResult Error( const std::string& msg, bool isFatal, const char* funcName, const char* fileName, unsigned int lineNum);

private:
	void WriteToLogFile(const std::string msg);
	void GetOutputBuffer(std::string& buffer, const std::string& tag, const std::string& msg, const char* funcName, const char* fileName, unsigned int lineNum);
	void OutputBufferToLogs(const std::string& buffer, unsigned char flags);

};
#pragma endregion

#pragma region LogManager Definition

LogManager::LogManager()
{
	SetDisplayFlags("INFO", LOG_FLAG_DEFAULT);
	SetDisplayFlags("WARNING", WARNING_FLAG_DEFAULT);
	SetDisplayFlags("ERROR", ERROR_FLAG_DEFAULT);

}
LogManager::~LogManager()
{
	for (auto it = m_errorMessengers.begin(); it != m_errorMessengers.end(); it++)
	{
		Logger::ErrorMessenger* messenger = (*it);
		delete messenger;
	}
	m_errorMessengers.clear();
}

void LogManager::SetDisplayFlags(const std::string& tag, unsigned char flag)
{
	if (flag != 0)
	{
		Tags::iterator findIt = m_Tags.find(tag);
		if (findIt == m_Tags.end())
			m_Tags.insert(std::make_pair(tag, flag));
		else
			findIt->second = flag;
	}
	else
		m_Tags.erase(tag);
}

void LogManager::Log(const std::string& tag, const std::string& msg, const char* funcName, const char* fileName, unsigned int lineNum) 
{
	Tags::iterator findIt = m_Tags.find(tag);
	if (findIt != m_Tags.end())
	{
		std::string buffer;
		GetOutputBuffer(buffer, tag, msg, funcName, fileName, lineNum);
		OutputBufferToLogs(buffer, findIt->second);
	}
}

void LogManager::AddErrorMessenger(Logger::ErrorMessenger* messenger) 
{
	S3D_ASSERT(messenger)
	m_errorMessengers.push_back(messenger);
}

LogManager::ErrorDialogResult LogManager::Error(const std::string& msg, bool isFatal, const char* funcName, const char* fileName, unsigned int lineNum)
{
	std::string tag = ((isFatal) ? "FATAL" : "ERROR");

	std::string buffer;

	GetOutputBuffer(buffer, tag, msg, funcName, fileName, lineNum);
	Tags::iterator findIt = m_Tags.find(tag);
	if (findIt != m_Tags.end())
	{
		OutputBufferToLogs(buffer, findIt->second);
	}

	// show dialog box

	int result = MessageBox(nullptr, buffer.c_str(), tag.c_str(), MB_ABORTRETRYIGNORE | MB_ICONERROR | MB_DEFBUTTON3);

	switch (result)
	{
		case IDIGNORE:
			return LogManager::ERROR_IGNORE;
		case IDABORT:
			__debugbreak(); // assembly instruction to open VS debugger.
			return LogManager::ERROR_ABORT;
		case IDRETRY:
			return LogManager::ERROR_RETRY_;
		default:
			return LogManager::ERROR_RETRY_;
	}
}

void LogManager::WriteToLogFile(const std::string log)
{
	FILE* file;
	fopen_s(&file, LOG_FILE, "a+");
	if (!file)
	{
		fprintf(stderr, "Unable to open log file %s for appending\n", LOG_FILE);
		return;
	}
	fprintf_s(file, log.c_str());
	fclose(file);
}

void LogManager::GetOutputBuffer(std::string& buffer, const std::string& tag, const std::string& msg, const char* funcName, const char* fileName, unsigned int lineNum)
{
	time_t now = time(nullptr);
	char dateBuffer[32];
	ctime_s(dateBuffer, sizeof dateBuffer, &now);
	std::string date(dateBuffer);

	buffer = "[" + date + "]";
	
	if (!tag.empty())
		buffer += tag + "-" + msg;
	else
		buffer += msg;
	
	if (funcName != nullptr)
	{
		buffer += "\nFunction: ";
		buffer += funcName;
	}
	
	if (fileName != nullptr)
	{
		buffer += "\n";
		buffer += fileName;
	}

	if (lineNum != 0)
	{
		buffer += "\nLine: ";
		char lineNumBuffer[11];
		memset(lineNumBuffer, 0, sizeof(char));
		buffer += _itoa(lineNum, lineNumBuffer, 10);
	}

	buffer += "\n";
}

void LogManager::OutputBufferToLogs(const std::string& buffer, unsigned char flags)
{
	// check what flags are set.
	if ((flags & WRITE_TO_LOG_FILE) > 0)
		WriteToLogFile(buffer);
	if ((flags & WRITE_TO_DEBUGGER) > 0)
		fprintf_s(stderr, buffer.c_str());
}

#pragma endregion

#pragma region ErrorMessenger Definition

Logger::ErrorMessenger::ErrorMessenger()
	: m_ErrorIgnored{false}
{
	s_pLogManager->AddErrorMessenger(this);
}

Logger::ErrorMessenger::~ErrorMessenger()
{}

void Logger::ErrorMessenger::Show(const std::string& msg, bool isFatal, const char* funcName, const char* fileName, unsigned int lineNum)
{
	if (!m_ErrorIgnored)
	{
		if (s_pLogManager->Error(msg, isFatal, funcName, fileName, lineNum) == LogManager::ERROR_IGNORE)
			m_ErrorIgnored = true;
	}
}

#pragma endregion

#pragma region Logger Namespace Function Definitions

namespace Logger {
	
	bool RestartLogFile()
	{
		FILE* file;
		fopen_s(&file, LOG_FILE, "w");
		if (!file)
		{
			fprintf(stderr, "Could not open log file %s\n", LOG_FILE);
			return false;
		}
		time_t now = time(nullptr);
		char date[32];
		ctime_s(date, sizeof date, &now);
		fprintf_s(file, "[%s]Log file %s opened for writing\n", date, LOG_FILE);
		fclose(file);

		return true;
	}
	
	void Init()
	{
		if (!s_pLogManager)
			s_pLogManager = DBG_NEW LogManager;
		RestartLogFile();
	}
	
	void Destroy()
	{
		delete s_pLogManager;
		s_pLogManager = nullptr;
	}
	
	void Log(std::string& tag, const std::string& msg, const char* funcName, const char* fileName, unsigned int lineNum)
	{
		S3D_ASSERT(s_pLogManager);
		s_pLogManager->Log(tag, msg, funcName, fileName, lineNum);
	}
}

#pragma endregion





