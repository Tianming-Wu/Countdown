@echo off
rem Countdown Autorun Registry Creator

%1 mshta vbscript:CreateObject("Shell.Application").ShellExecute("cmd.exe","/c %~s0 ::","","runas",1)(window.close)&&exit

if not exist "Countdown.exe" goto EOF

set "inst=%cd%"
if not "%inst:~-1%"=="\" set "inst=%inst%\"
set "inst=%inst:\=\\%"

echo Windows Registry Editor Version 5.00>autorun.reg.tmp
echo.>>autorun.reg.tmp
echo [HKEY_CURRENT_USER\SOFTWARE\Microsoft\Windows\CurrentVersion\Run]>>autorun.reg.tmp
echo \"Countdown\"=\"%inst%Countdown.exe\"

regedit /s autorun.reg.tmp
del autorun.reg.tmp

:EOF
