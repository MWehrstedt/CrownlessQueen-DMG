@echo off

REM Compile Script. Compiles for DMG and GG
REM Usage:
REM     compile.bat [-nostart]
REM     compile.bat [-nobuild]

mkdir -p obj

SET COMP_STRING=
SET GAME_TITLE="SHEERCOLD  "
SET GAME_RESULT=sheercold.gb
SET GAME_RESULT_SG=sheercold.gg

SET PATH_BGB=..\..\Tools\bgb\bgb.exe
SET PATH_GEARSYSTEM=..\..\..\GameGear\Tools\Gearsystem\Gearsystem.exe

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

for /f %%f in ('dir res\gb\*.c /b') do (
    bin\lcc -c -o obj\gb\%%~nf.o res\gb\%%~nf.c -debug
    ECHO res\gb\%%f
    SET COMP_STRING=!COMP_STRING! obj\gb\%%~nf.o
)

REM source files
ECHO -- Compiling source files --
for /f %%f in ('dir src\*.c /b') do (
    bin\lcc -c -o obj\%%~nf.o src\%%~nf.c -debug
    ECHO res\%%f
    SET COMP_STRING=!COMP_STRING! obj\%%~nf.o
)

for /f %%f in ('dir src\gb\*.c /b') do (
    bin\lcc -c -o obj\gb\%%~nf.o src\gb\%%~nf.c -debug
    ECHO src\gb\%%f
    SET COMP_STRING=!COMP_STRING! obj\gb\%%~nf.o
)


ECHO obj\%GAME_RESULT%

bin\lcc -o obj\%GAME_RESULT% %COMP_STRING% -Wm-yn%GAME_TITLE% -Wl-yt0x19 -Wl-j -Wm-yoA -Wm-ys -autobank -Wb-ext=.rel -Wb-v -debug
rem bin\lcc -o obj\%GAME_RESULT% %COMP_STRING% res/hUGEDriver.lib -Wm-yn%GAME_TITLE% -debug

ECHO %COMP_STRING%
ECHO === End Compile %GAME_RESULT% ===

SET COMP_STRING=

ECHO --
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

for /f %%f in ('dir res\gg\*.c /b') do (
    bin\lcc -c -o obj\gg\%%~nf.o res\gg\%%~nf.c -mz80:gg -debug
    ECHO res\gg\%%f
    SET COMP_STRING=!COMP_STRING! obj\gg\%%~nf.o
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

ECHO -- Start GB ROM in BGB --
START %PATH_BGB% obj\%GAME_RESULT%

ECHO -- Start GG ROM in Gearsystem --
START %PATH_GEARSYSTEM% obj\%GAME_RESULT_SG%

:SCRIPTEND
ECHO == DONE ===
