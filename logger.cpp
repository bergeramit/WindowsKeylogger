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
    string &sLoggerPath,
    string sLoggerFilename
    )
{
    string fullName = sLoggerPath + "\\" + sLoggerFilename;
    strcpy(this->m_loggerFullPath, fullName.c_str());
    this->m_loggerHandler = CreateFile(
        this->m_loggerFullPath,
        FILE_APPEND_DATA,
        FILE_SHARE_WRITE,
        NULL,
        OPEN_ALWAYS,
        FILE_ATTRIBUTE_NORMAL | FILE_FLAG_WRITE_THROUGH,
        NULL);

    debugPrintReturnCode();
/*
    if (this->m_loggerHandler == INVALID_HANDLE_VALUE)
    {
      // Failed to open/create file
      throw 1;
    }
    */
}

Logger::Logger(
    string &sloggerFullPath
    )
{
    strcpy(this->m_loggerFullPath, sloggerFullPath.c_str());
    this->m_loggerHandler = CreateFile(
        (LPCSTR)&(this->m_loggerFullPath),
        FILE_APPEND_DATA,
        FILE_SHARE_READ,
        NULL,
        OPEN_ALWAYS,
        FILE_ATTRIBUTE_NORMAL | FILE_FLAG_WRITE_THROUGH,
        NULL);

    debugPrintReturnCode();
/*
    if (this->m_loggerHandler == INVALID_HANDLE_VALUE)
    {
      // Failed to open/create file
      throw 1;
    }
    */
}

Logger::~Logger()
{
    CloseHandle(this->m_loggerHandler);
    debugPrintReturnCode();
}

eLoggerStatus Logger::log(const char *value, int size)
{
    eLoggerStatus rc = LOGGER_UNDEFINED;
    DWORD bytesWritten;
    WriteFile(m_loggerHandler, value, size, &bytesWritten, NULL);

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

eLoggerStatus Logger::logLine(const char *value, int size)
{
    char *sFullLine = new char[size + 1];
    strncpy(sFullLine, value, size);
    sFullLine[size] = '\n';

    return this->log(sFullLine, size + 1);
}

void Logger::hide()
{
    DWORD attributes = GetFileAttributes(this->m_loggerFullPath);
    SetFileAttributes(this->m_loggerFullPath, attributes | FILE_ATTRIBUTE_HIDDEN);
    debugPrintReturnCode();
}
