@echo off
rem record_play.bat [NAME] - play the game with the keyboard while the buttons are recorded, for a
rem new A/B test input (instance 2: tools/ab_inputs/README.md, "Recorded play"). Double-click it
rem and type a name, or run it with the name.
rem
rem It copies the game's starting state (nand, settings.ini, wiimotes.ini, profiles.json) to
rem game\recordings\NAME\start\, then starts game\nsmbw.exe in deterministic mode with:
rem   game\recordings\NAME\input.rec   - the keyboard's buttons per video field
rem   game\recordings\NAME\check.hash  - a hash of the game's memory every second (to check the replay)
rem Play with the keyboard only (no Wii Remotes connected), don't load save states, don't go online,
rem and stay out of the PC port's own Options / Controls menus. Quit the game when you're done.
setlocal
set "NAME=%~1"
if "%NAME%"=="" set /p "NAME=Name for this recording (for example yoshi): "
if "%NAME%"=="" goto :fail
rem (the game folder: next to this file, or recomp\tools\..\..\game, or ..\game)
set "GAME="
for %%d in ("%~dp0." "%~dp0..\..\game" "%~dp0..\game" "%CD%") do if not defined GAME if exist "%%~d\nsmbw.exe" set "GAME=%%~fd"
if not defined GAME (
  echo Can't find nsmbw.exe next to this file or in ..\..\game - put record_play.bat in the game folder.
  goto :fail
)
echo Game folder: %GAME%
set "OUT=%GAME%\recordings\%NAME%"
if exist "%OUT%\input.rec" (
  echo %OUT% already has a recording - pick another name.
  goto :fail
)
mkdir "%OUT%\start" 2>nul
xcopy /e /i /q /y "%GAME%\nand" "%OUT%\start\nand" >nul
for %%f in (settings.ini wiimotes.ini profiles.json) do if exist "%GAME%\%%f" copy /y "%GAME%\%%f" "%OUT%\start\" >nul
set RT_DETERMINISTIC=1
set RT_UPDATE=0
set "RT_REC=%OUT%\input.rec"
set "RT_DET_HASH=%OUT%\check.hash"
set RT_DET_HASH_EVERY=60
set RT_DET_HASH_LIVE=1
echo Recording to %OUT%
echo Play with the keyboard, then quit the game.
pushd "%GAME%"
nsmbw.exe
popd
if exist "%OUT%\input.rec" (
  echo Done: %OUT%
) else (
  echo The game didn't write %OUT%\input.rec - is nsmbw.exe rebuilt with the recorder ^(part 113^)?
)
pause
exit /b 0
:fail
pause
exit /b 1
