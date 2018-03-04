@echo off

setlocal
if  "%ESTEREL%" == "" goto error

set XSTRL_LIB=%ESTEREL%\lib\xesterel
set WISH=%ESTEREL%\bin\strlsh.exe

%WISH% %XSTRL_LIB%\xesterel %*
goto end

:error
echo ESTEREL environment variable is unset
:end

endlocal
