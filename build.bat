@echo off
echo ��������ļ�

taskkill /f /im Trochilus.exe
taskkill /f /im Generator.exe

echo �������ƶ�����
copy /Y "%cd%\server\bin\master.dll" "%cd%\bin\bin\master.dll"
copy /Y "%cd%\server\bin\midutils.dll" "%cd%\bin\bin\midutils.dll" 
copy /Y "%cd%\server\bin\Trochilus.exe" "%cd%\bin\bin\Trochilus.exe"
copy /Y "%cd%\client\bin\body.dll" "%cd%\bin\bin\modules\svtlogo.dll"

echo ��������������
copy /Y "%cd%\client\bin\Generator.exe" "%cd%\bin\Generator\Generator.exe"
copy /Y "%cd%\client\bin\shell.dll" "%cd%\bin\Generator\bingo\shell.dll"

start "" "%cd%\bin\bin\Trochilus.exe"
timeout /t 2 /nobreak > nul
taskkill /f /im Trochilus.exe"
copy /Y "%cd%\bin\bin\modules\svtlogo.r" "%cd%\bin\Generator\bingo\svtlogo.dat"

del "%cd%\bin\bin\modules\svtlogo.r"
del "%cd%\bin\bin\modules\svtlogo.dll"

pause
echo ������ϣ�