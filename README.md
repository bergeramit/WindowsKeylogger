# WindowsKeylogger

## Compile
g++ ./main.cpp ./key_listener.cpp ./logger.cpp -std=c++14 -o klaf.exe

## Compile with Debug output
g++ ./main.cpp ./key_listener.cpp ./logger.cpp -std=c++14 -o klaf.exe -DDEBUG

## Usage
klaf.exe ==DIR_TO_KEYLOGGER_LOGS==

# Version 1.1 release
### Features
1. Fixed bug that makes it possible to append to the already exists file
2. get path to log file from the cmd


# Last Versions - Release Notes
## Version 1.0 release
### Features
1. log is written to a hidden file in C:\temp (configurable in main.cpp)
2. log keys outside of the console
### To-Do
1. does not understand multi keys presses
2. win32 cpp conventions is terribly implemented
3. console windows left open
4. no timestamps or debug logs
5. get the path to the files from the cmd

### Bugs
1. could not append to the file nor open it after the first use



