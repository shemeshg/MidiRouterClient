#!/bin/zsh
script_dir=$(dirname $(realpath "$0"))

cd "$script_dir/.."
if [ ! -d ".venv" ]; then
    python3 -m venv .venv
    source .venv/bin/activate
    pip install cogapp
else
    source .venv/bin/activate
fi


cd "$script_dir/.."
cd Bal/RtMidiRouterLib/MidiClient/genPrpt
cog -r *.hpp

cd "$script_dir/.."
cd Bal
cog -r BalDataPrivate.h BalDataPrivate.cpp BalData.h BalData.cpp

cd "$script_dir/.."
cd Bal/RtMidiRouterLib
cog -r CMakeLists.txt

cd "$script_dir/.."
cd Bal/RtMidiRouterLib/MidiClient
cog -r CMakeLists.txt
