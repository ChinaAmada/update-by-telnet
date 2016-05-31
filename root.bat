@echo off

color 2f
::start /b tftpd32.exe


CHOICE /C yn /M "确定要更新程序吗?"
IF Errorlevel 2 goto No
IF Errorlevel 1 goto Yes


:Yes
::echo "sucess"
echo 正在更改本机IP地址...
netsh interface ipv4 set address name="本地连接" source=static addr=192.168.100.244 mask=255.255.255.0 gateway=192.168.100.1 gwmetric=0 >nul
choice /t 2 /d y /n >nul
start /b tftpd32.exe
choice /t 2 /d y /n >nul
update.exe 192.168.100.195 23 192.168.100.244 cmd.sh
IF Errorlevel 1 goto FF
IF Errorlevel 0 goto SS
exit

:No
echo "取消成功"
pause
exit



:FF
echo "更新失败，请检查网络和硬件状态！"
pause
exit


:SS
echo "更新成功！"
pause
exit