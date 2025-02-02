set CMAKE_PATH="C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe"
echo %CMAKE_PATH%

IF NOT EXIST "%CD%\build" GOTO RUNCMAKE
SET /P CLEANBUILD="clean build directory (Y/[N])?  "
IF /I "%CLEANBUILD%"=="Y" {
   echo.removing old build contents
   del /S /Q "%CD%\build\*.*"


:RUNCMAKE

%CMAKE_PATH% -S . -B build/
rem %CMAKE_PATH% --build build/ --target sample.exe
%CMAKE_PATH% --build build/
