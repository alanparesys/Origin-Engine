@echo off
setlocal enabledelayedexpansion

echo Cloning GLFW repository...
if exist glfw rmdir /s /q glfw
git clone https://github.com/glfw/glfw.git

if not exist glfw (
    echo Failed to clone GLFW. Check git installation.
    pause
    exit /b 1
)

cd glfw

echo Generating build files with CMake (static, VS generator)...
if exist build rmdir /s /q build
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022" -A x64 -DBUILD_SHARED_LIBS=OFF -DGLFW_BUILD_DOCS=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_EXAMPLES=OFF

if errorlevel 1 (
    echo CMake generation failed. Ensure CMake and VS are installed.
    pause
    exit /b 1
)

echo Building GLFW static library (Release and Debug)...
cmake --build . --config Release
cmake --build . --config Debug

if errorlevel 1 (
    echo Build failed.
    pause
    exit /b 1
)

cd ..\..

echo Copying static libraries...
copy /y glfw\build\src\Release\glfw3.lib Library\lib\Release\glfw3.lib
copy /y glfw\build\src\Debug\glfw3.lib Library\lib\Debug\glfw3.lib

echo Copying headers...
mkdir include\GLFW 2>nul
xcopy /s /i /y glfw\include\GLFW\* Library\include\GLFW\

echo Done! Static libs in Library\lib\, headers in Library\include\GLFW\

pause