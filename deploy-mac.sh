#!/bin/sh
# git tag 2.5.0
# git push --tags 
# or
# git push origin 2.0.5
mkdir deploye
cd deploye
~/Qt/6.9.1/macos/bin/qt-cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=. ../MidiRouterClient
cmake --build .
cmake --install .

#mv midi-router-client.app "Pass simple.app"
#zip -r -y midi-router-client-macos_0.99.0.zip ./Pass\ simple.app
cpack -G DragNDrop

mkdir out
cp -R "midi-router-client.app" out;
ln -s /Applications out;
hdiutil create -volname "midi-router-client" -srcfolder out -ov -format UDZO midi-router-client-2.0.0-arm64.dmg


sha256sum midi-router-client-1.0.19-arm64.dmg

# sftp iuqwer9@frs.sourceforge.net

# sftp> cd /home/frs/project/midi-router-client
# sftp> rm midi-router-client-osx_0.55.0.dmg
# sftp> put midi-router-client-macos_0.56.0.dmg
