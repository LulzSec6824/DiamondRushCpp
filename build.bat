@echo off
echo ===== Diamond Rush Build Script =====

:: Create build directory if it doesn't exist
if not exist build mkdir build

:: Configure and build
cd build
cmake -G "MinGW Makefiles" ..
cmake --build .

echo Build completed successfully!
echo Run the game with: .\DiamondRush.exe

cd ..
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