@echo off

color 2f
::start /b tftpd32.exe


CHOICE /C yn /M "ȷ��Ҫ���³�����?"
IF Errorlevel 2 goto No
IF Errorlevel 1 goto Yes


:Yes
::echo "sucess"
echo ���ڸ��ı���IP��ַ...
netsh interface ipv4 set address name="��������" source=static addr=192.168.100.244 mask=255.255.255.0 gateway=192.168.100.1 gwmetric=0 >nul
choice /t 2 /d y /n >nul
start /b tftpd32.exe
choice /t 2 /d y /n >nul
update.exe 192.168.100.195 23 192.168.100.244 cmd.sh
IF Errorlevel 1 goto FF
IF Errorlevel 0 goto SS
exit

:No
echo "ȡ���ɹ�"
pause
exit



:FF
echo "����ʧ�ܣ����������Ӳ��״̬��"
pause
exit


:SS
echo "���³ɹ���"
pause
exit