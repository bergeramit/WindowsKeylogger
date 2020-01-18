#include <string>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <bits/stdc++.h>

#include "logger.h"

using namespace std;

#ifdef DEBUG
void printError()
{
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
    printf("Failed with: %s\n", (LPTSTR)lpMsgBuf);

    LocalFree(lpMsgBuf);
}
#endif

Logger::Logger(
    string &sLoggerPath,
    string sLoggerFilename
    )
{
    string fullName = sLoggerPath + "\\" + sLoggerFilename;
    strcpy(this->m_loggerFullPath, fullName.c_str());
    this->m_loggerHandler = CreateFile(
        this->m_loggerFullPath,
        GENERIC_WRITE,
        FILE_SHARE_WRITE,
        NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL);

#ifdef DEBUG
    printError();
#endif
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
        GENERIC_WRITE,
        FILE_SHARE_READ,
        NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL
        NULL);

#ifdef DEBUG
    printError();
#endif
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

#ifdef DEBUG
    printError();
#endif
}

eLoggerStatus Logger::logLine(const char *value, int size)
{
    DWORD bytesWritten;
    WriteFile(m_loggerHandler, value, size, &bytesWritten, NULL);
    WriteFile(m_loggerHandler, "\n", 1, &bytesWritten, NULL);
}

eLoggerStatus Logger::log(const char *value, int size)
{
    DWORD bytesWritten;
    WriteFile(m_loggerHandler, value, size, &bytesWritten, NULL);
}

void Logger::hide()
{
    DWORD attributes = GetFileAttributes(this->m_loggerFullPath);
    SetFileAttributes(this->m_loggerFullPath, attributes | FILE_ATTRIBUTE_HIDDEN);

#ifdef DEBUG
    printError();
#endif
}
