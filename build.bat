@ECHO off
ECHO Checking CMake...
WHERE cmake >nul 2>nul
IF %ERRORLEVEL% NEQ 0 (
    ECHO CMake wasn't found on your device.
    ECHO Please go to https://cmake.org/ to install CMake. 
    PAUSE
) ELSE (
    ECHO CMake was found.
    IF NOT EXIST build (
        MD build
        CD .>.gitkeep
    )
    CD build
    cmake ..
)