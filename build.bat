@echo off
setlocal enabledelayedexpansion

echo ===== Diamond Rush Build Script =====

:: Check for CMake
where cmake >nul 2>nul
if %ERRORLEVEL% neq 0 (
    echo ERROR: CMake not found. Please install CMake and add it to your PATH.
    exit /b 1
)

:: Set build type based on argument
set BUILD_TYPE=Debug
if "%1"=="release" set BUILD_TYPE=Release

:: Create build directory if it doesn't exist
if not exist build mkdir build

:: Configure and build the project
echo Configuring project with CMake...
cd build
cmake -DCMAKE_BUILD_TYPE=%BUILD_TYPE% -DBUILD_DEBUG=%BUILD_TYPE% ..
if %ERRORLEVEL% neq 0 (
    echo ERROR: CMake configuration failed.
    exit /b 1
)

echo Building project...
cmake --build . --config %BUILD_TYPE%
if %ERRORLEVEL% neq 0 (
    echo ERROR: Build failed.
    exit /b 1
)

:: Check if bin directory exists, create if not
if not exist bin mkdir bin

:: Copy executable to bin directory if not already there
if not exist bin\DiamondRush.exe (
    if exist DiamondRush.exe copy DiamondRush.exe bin\
)

echo.
echo ===== Build completed successfully! =====
echo.
echo Run the game with: .\build\bin\DiamondRush.exe
echo.

cd ..
endlocal