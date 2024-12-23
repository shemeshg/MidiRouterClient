#!/bin/zsh

cd ..
if [ ! -d ".venv" ]; then
    python3 -m venv .venv
    source .venv/bin/activate
    pip install cogapp
else
    source .venv/bin/activate
fi

cd Bal/RtMidiRouterLib/MidiClient/genPrpt
cog -r *.h *.cpp