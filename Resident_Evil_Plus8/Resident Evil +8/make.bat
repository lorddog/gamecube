@ECHO OFF

SET DEVKITCUBE=c:\gc\devkitcube
SET PATH=%DEVKITCUBE%\bin;%DEVKITCUBE%\tools;%PATH%

make -s
IF ERRORLEVEL 1 GOTO error

bin\psoload -i192.168.1.100 trainer.dol
GOTO end

:error
ECHO Compile Error! :(
pause

:end
cls