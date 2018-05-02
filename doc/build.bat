@ECHO off
ECHO Checking Doxygen...
WHERE doxygen >nul 2>nul
IF %ERRORLEVEL% NEQ 0 (
    ECHO Doxygen wasn't found on your device.
    ECHO Please visit http://www.doxygen.nl/ to install Doxygen. 
    PAUSE
) ELSE (
    ECHO Doxygen was found.
    doxygen Doxyfile
)
