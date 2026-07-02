@echo off
setlocal EnableExtensions
set "ROOT=%~dp0"
set "PREMAKE=%ROOT%tools\premake5\premake5.exe"
set "PREMAKE_FILE=%ROOT%premake5.lua"
set "SANDBOX_FLAG="

if /i "%~1"=="-s" (
    set "SANDBOX_FLAG=--sandbox"
)

if not exist "%PREMAKE%" (
    echo Error: Premake executable not found:
    echo   "%PREMAKE%"
    exit /b 1
)

call "%PREMAKE%" --file="%PREMAKE_FILE%" %SANDBOX_FLAG% vs2026
exit /b %ERRORLEVEL%