@echo off
setlocal EnableExtensions

set "ROOT=%~dp0"

if not exist "%ROOT%premake5.lua" (
    echo Error: premake5.lua not found.
    echo This script must be run from the project root.
    exit /b 1
)

if exist "%ROOT%bin\" (
    rmdir /s /q "%ROOT%bin"
)

if exist "%ROOT%build\" (
    rmdir /s /q "%ROOT%build"
)

del /s /q "%ROOT%*.sln" 2>nul
del /s /q "%ROOT%*.slnx" 2>nul
del /s /q "%ROOT%*.vcxproj*" 2>nul

endlocal