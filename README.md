# WindowsKeylogger

Key logger in C++

## Usage
run Start_Klogger.ps1 in powershell

## Compile
g++ ./main.cpp ./key_listener.cpp ./logger.cpp -std=c++14 -o OUTPUT_EXE

## Compile with Debug output
g++ ./main.cpp ./key_listener.cpp ./logger.cpp -std=c++14 -o OUTPUT_EXE -DDEBUG

# Version 2.0 release Notes
### Features
1. Fixed bug that makes it possible to append to the already exists file
2. get path to log file from the cmd
3. Easily run using a powershell script
4. Hidden console and Background proccess
### To-Do
1. does not understand multi keys presses
2. win32 cpp conventions is terribly implemented
3. no timestamps or debug logs
4. get log files names from the cmd line/ runner script
### Bugs
1. do not handle file name that makes it unable to run (due to privilages)
2. log's dir is given to the proccess as command line args which makes it easy to see.

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



