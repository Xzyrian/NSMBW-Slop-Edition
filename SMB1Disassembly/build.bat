@echo off

IF EXIST code\settings.asm goto dontMakeSettings
echo Creating code\settings.asm...
echo ; Local settings>code\settings.asm
echo ; Check settings.default.asm for a list of settings>>code\settings.asm
:dontMakeSettings

rem This time/date code fails on some systems
echo .db "V %date:~10,4% %date:~4,2% %date:~7,2%">data\version.asm
rem asm6\SpiderDave\asm6f -L -q main.asm SMBBase.nes list.txt
asm6\parasyte\asm6 -L -q main.asm SMBBase.nes list.txt

IF NOT EXIST SMBBase.nes goto error
goto theend

:error
pause
exit

:theend
start SMBBase.nes
