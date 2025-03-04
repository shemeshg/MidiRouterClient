#!/bin/sh

# cd /Users/macos/Qt/6.8.0/Src/
# mkdir /Users/macos/DATA/develop/Qt6.8Static
# ./configure -release -static -opensource -confirm-license -prefix /Users/macos/DATA/develop/Qt6.8Static
# cmake --build . --parallel
# cmake --install .

rm -rf /Volumes/RAM_Disk_4G/out
mkdir /Volumes/RAM_Disk_4G/out
cd /Volumes/RAM_Disk_4G/out
/Users/macos/DATA/develop/Qt6.8Static/bin/qt-cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=. /Users/macos/DATA/develop/midi-router-client
cmake --build .
cmake --install .
