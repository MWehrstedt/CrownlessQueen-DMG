@echo off

REM Compile Script. Compiles for DMG only
REM Usage:
REM     compile.bat [-nostart]

mkdir -p obj

SET COMP_STRING=
SET GAME_TITLE="SHEERCOLD  "
SET GAME_RESULT=sheercold.gb

SET PATH_BGB=..\..\Tools\bgb\bgb.exe

SETLOCAL EnableDelayedExpansion

IF "%~1"=="-nobuild" GOTO SKIPBUILD

ECHO === Start Compile %GAME_RESULT% ===

REM resource files
ECHO -- Compiling resource files --
for /f %%f in ('dir res\SFX\*.c /b') do (
    bin\lcc -c -o obj\%%~nf.o res\SFX\%%~nf.c -debug
    ECHO res\SFX\%%f
    SET COMP_STRING=!COMP_STRING! obj\%%~nf.o
)

for /f %%f in ('dir res\*.c /b') do (
    bin\lcc -c -o obj\%%~nf.o res\%%~nf.c -debug
    ECHO res\%%f
    SET COMP_STRING=!COMP_STRING! obj\%%~nf.o
)

REM source files
ECHO -- Compiling source files --
for /f %%f in ('dir src\*.c /b') do (
    bin\lcc -c -o obj\%%~nf.o src\%%~nf.c -debug
    ECHO res\%%f
    SET COMP_STRING=!COMP_STRING! obj\%%~nf.o
)

ECHO obj\%GAME_RESULT%

bin\lcc -o obj\%GAME_RESULT% %COMP_STRING% -Wm-yn%GAME_TITLE% -Wl-yt0x19 -Wl-j -Wm-yoA -Wm-ys -autobank -Wb-ext=.rel -Wb-v -debug
rem bin\lcc -o obj\%GAME_RESULT% %COMP_STRING% res/hUGEDriver.lib -Wm-yn%GAME_TITLE% -debug

ECHO %COMP_STRING%
ECHO === End Compile %GAME_RESULT% ===

:SKIPBUILD

IF "%~1"=="-nostart" GOTO SCRIPTEND

ECHO -- Start GB ROM in BGB --
%PATH_BGB% obj\%GAME_RESULT%

:SCRIPTEND
ECHO == DONE ===
