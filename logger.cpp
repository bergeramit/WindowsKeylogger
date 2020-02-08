#include <string>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <cstring>
#include <bits/stdc++.h>

#include "logger.h"

using namespace std;


/*
 * This funciton only does something if -DDEBUG is used in compilation.
 */
void debugPrintReturnCode()
{
#ifdef DEBUG
    LPVOID lpMsgBuf;
    DWORD dw = GetLastError();

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &lpMsgBuf,
        0, NULL );
    printf("Return Code: %s\n", (LPTSTR)lpMsgBuf);

    LocalFree(lpMsgBuf);
#endif
    return;
}

Logger::Logger(
    string &dir,
    string file_name
    )
{
    string fullName = dir + "\\" + file_name;
    strcpy(this->full_path, fullName.c_str());
    this->file_handler = CreateFile(
        this->full_path,
        FILE_APPEND_DATA,
        FILE_SHARE_WRITE,
        NULL,
        OPEN_ALWAYS,
        FILE_ATTRIBUTE_NORMAL | FILE_FLAG_WRITE_THROUGH,
        NULL);

    debugPrintReturnCode();
/*
    if (this->file_handler == INVALID_HANDLE_VALUE)
    {
      // Failed to open/create file
      throw 1;
    }
    */
}

Logger::Logger(
    string &path
    )
{
    strcpy(this->full_path, path.c_str());
    this->file_handler = CreateFile(
        (LPCSTR)&(this->full_path),
        FILE_APPEND_DATA,
        FILE_SHARE_READ,
        NULL,
        OPEN_ALWAYS,
        FILE_ATTRIBUTE_NORMAL | FILE_FLAG_WRITE_THROUGH,
        NULL);

    debugPrintReturnCode();
/*
    if (this->file_handler == INVALID_HANDLE_VALUE)
    {
      // Failed to open/create file
      throw 1;
    }
    */
}

Logger::~Logger()
{
    CloseHandle(this->file_handler);
    debugPrintReturnCode();
}

LOGGER_Status_t Logger::LOGGER_log(const char *value, int size)
{
    LOGGER_Status_t rc = LOGGER_UNDEFINED;
    DWORD bytesWritten;
    WriteFile(file_handler, value, size, &bytesWritten, NULL);

    debugPrintReturnCode();

    if (bytesWritten != size) {
        cout << "bytesWritten: " << bytesWritten << "size" << size << "value" << value << endl;
        rc = LOGGER_ERROR_FAILED_TO_LOG;
        goto Exit;
    }

    rc = LOGGER_SUCCESS;
Exit:
    return rc;
}

LOGGER_Status_t Logger::LOGGER_log_line(const char *value, int size)
{
    char *sFullLine = new char[size + 1];
    strncpy(sFullLine, value, size);
    sFullLine[size] = '\n';

    return this->LOGGER_log(sFullLine, size + 1);
}

void Logger::hide()
{
    DWORD attributes = GetFileAttributes(this->full_path);
    SetFileAttributes(this->full_path, attributes | FILE_ATTRIBUTE_HIDDEN);
    debugPrintReturnCode();
}
