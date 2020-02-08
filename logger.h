#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>
#include <windows.h>

using namespace std;

#define LOGGER_MAX_PATH_SIZE (1000)
#define LOGGER_MAX_MULTI_KEYS (10)

enum LOGGER_Status_t {
	LOGGER_UNDEFINED,
	LOGGER_SUCCESS,
	LOGGER_ERROR_FAILED_TO_LOG,
	LOGGER_ERROR
};

class Logger {
	public:

		Logger(string &path);
		Logger(string &dir, string file_name);
		~Logger();
		LOGGER_Status_t LOGGER_log_line(const char *value, int size);
		LOGGER_Status_t LOGGER_log(const char *value, int size);
		void hide();

	private:
		char full_path[LOGGER_MAX_PATH_SIZE];
		HANDLE file_handler;
};

#endif /* LOGGER_H */