CALL  "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" amd64
D: 
cd D:\projects\midi-router-client
git pull
cd gpgfactory
git pull
R:
cd \
mkdir deployed
cd deployed
call D:\Qt\6.8.0\msvc2022_64\bin\qt-cmake -GNinja -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=. D:\projects\MidiRouterClient
call ninja

rmdir /s/q R:\WinDll
mkdir R:\WinDll
copy R:\deployed\src\rnp\*.dll R:\WinDll
copy D:\projects\midi-router-client\icon.ico R:\WinDll

cpack -G ZIP
cpack -G NSIS
REM # D:\Qt\6.7.1\msvc2019_64\bin\windeployqt.exe  --qmldir D:\projects\midi-router-client pass-simple.exe
REM # cd \
REM # move deployed pass-simple-windows-x64
REM # powershell -Command "Compress-Archive -Path r:\pass-simple-windows-x64 -DestinationPath midi-router-client-1.0.4_win_x64.zip"
REM # rmdir /s/q pass-simple-windows-x64

