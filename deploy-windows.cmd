CALL  "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" amd64
R:
mkdir build
cd build
call D:\Qt\6.8.0\msvc2022_64\bin\qt-cmake -GNinja -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=. D:\projects\MidiRouterClient
call ninja

cpack -G ZIP
cpack -G NSIS

