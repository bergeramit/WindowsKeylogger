#ifndef KEY_LISTENER_EXPORTS_H
#define KEY_LISTENER_EXPORTS_H

#include <string>
#include <fstream>
#include <windows.h>

using namespace std;

enum KLOGGER_error_codes_t {
	SUCCESS,
	ERROR_BAD_ARGS,
	ERROR_INIT_CALLED_MORE_THAN_ONCE,
	ERROR_BEGIN_LOGGING_CALLED_BEFORE_INIT,
	UNDEFINED
};

KLOGGER_error_codes_t KLOGGER_init_klogger(string &dir_to_save_logs);
KLOGGER_error_codes_t KLOGGER_begin_logging(void);

#endif /* KEY_LISTENER_EXPORTS_H */