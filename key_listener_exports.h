#ifndef KEY_LISTENER_EXPORTS_H
#define KEY_LISTENER_EXPORTS_H

#include <string>
#include <fstream>
#include <windows.h>

using namespace std;

enum eKLoggerStatus {
	SUCCESS,
	ERROR_INIT_CALLED_MORE_THAN_ONCE,
	ERROR_BEGIN_LOGGING_CALLED_BEFORE_INIT,
	UNDEFINED
};

eKLoggerStatus initKLogger(string &sKLogPath);
eKLoggerStatus beginLogging(void);

#endif /* KEY_LISTENER_EXPORTS_H */