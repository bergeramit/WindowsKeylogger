#include <iostream>

#include "key_listener_exports.h"

using namespace std;

#define LOG_PATH ("C:\\temp")

int main(int argc, const char *argv[]) {
    eKLoggerStatus rc = UNDEFINED;
    string path = LOG_PATH;

    rc = initKLogger(path);
    if (SUCCESS == rc) {
        cout << "Init Successfully" << endl;
    }

    rc = beginLogging();
    if (SUCCESS == rc) {
        cout << "Finished Successfully" << endl;
    }

    return rc;
}