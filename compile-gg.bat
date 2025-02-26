@echo off

REM Compile Script. GG only
REM Usage:
REM     compile.bat [-nostart]
REM     compile.bat [-nobuild]

mkdir -p obj

SET COMP_STRING=
SET GAME_TITLE="OWLS "
SET GAME_RESULT_SG=powl.gg

SET PATH_GEARSYSTEM=..\..\..\GameGear\Tools\Gearsystem\Gearsystem.exe

SETLOCAL EnableDelayedExpansion

IF "%~1"=="-nobuild" GOTO SKIPBUILD

ECHO === Start Compile %GAME_RESULT_SG% ===

REM resource files
ECHO -- Compiling resource files --
for /f %%f in ('dir res\SFX\*.c /b') do (
    bin\lcc -c -o obj\%%~nf.o res\SFX\%%~nf.c -mz80:gg -debug
    ECHO res\SFX\%%f
    SET COMP_STRING=!COMP_STRING! obj\%%~nf.o
)

for /f %%f in ('dir res\*.c /b') do (
    bin\lcc -c -o obj\%%~nf.o res\%%~nf.c -mz80:gg -debug
    ECHO res\%%f
    SET COMP_STRING=!COMP_STRING! obj\%%~nf.o
)

REM source files
ECHO -- Compiling source files --
for /f %%f in ('dir src\*.c /b') do (
    bin\lcc -c -o obj\%%~nf.o src\%%~nf.c -mz80:gg -debug
    ECHO res\%%f
    SET COMP_STRING=!COMP_STRING! obj\%%~nf.o
)

ECHO obj\%GAME_RESULT_SG%

bin\lcc -o obj\%GAME_RESULT_SG% %COMP_STRING% -Wm-yn%GAME_TITLE% -Wl-j -Wm-yoA -autobank -Wb-ext=.rel -Wb-v -mz80:gg -debug
rem bin\lcc -o obj\%GAME_RESULT% %COMP_STRING% res/hUGEDriver.lib -Wm-yn%GAME_TITLE% -debug

ECHO %COMP_STRING%
ECHO === End Compile %GAME_RESULT_SG% ===

:SKIPBUILD

IF "%~1"=="-nostart" GOTO SCRIPTEND

ECHO -- Start GG ROM in Gearsystem --
%PATH_GEARSYSTEM% obj\%GAME_RESULT_SG%

:SCRIPTEND
ECHO == DONE ===
