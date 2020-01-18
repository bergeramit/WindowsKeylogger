#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>
#include <windows.h>

using namespace std;

#define LOGGER_MAX_PATH_SIZE (1000)
#define LOGGER_MAX_MULTI_KEYS (10)

enum eLoggerStatus {
	LOGGER_UNDEFINED,
	LOGGER_SUCCESS,
	LOGGER_ERROR
};

class Logger {
	public:

		Logger(string &sloggerFullPath);
		Logger(string &sLoggerPath, string sLoggerFilename);
		~Logger();
		eLoggerStatus logLine(const char *value, int size);
		eLoggerStatus log(const char *value, int size);
		void hide();

	private:
		char m_loggerFullPath[LOGGER_MAX_PATH_SIZE];
		HANDLE m_loggerHandler;
};

#endif /* LOGGER_H */