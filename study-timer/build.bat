@echo off
REM Study Timer Build Script for Windows
echo Building Study Timer...

if not exist build mkdir build
cd build

REM Compile with g++ if available
g++ -std=c++17 -Wall ../src/main.cpp ../src/timer.cpp ../src/storage.cpp ../src/ui.cpp -o study-timer.exe -I../include -lws2_32

if %ERRORLEVEL% EQU 0 (
    echo.
    echo Build successful!
    echo Run: .\study-timer.exe
) else (
    echo Build failed. Make sure g++ (MinGW) is installed.
    pause
)
