#!/bin/zsh
script_dir=$(dirname "$0")
cd "$script_dir/.."
if [ ! -d ".venv" ]; then
    python3 -m venv .venv
    source .venv/bin/activate
    pip install cogapp
else
    source .venv/bin/activate
fi

cd Bal/RtMidiRouterLib/MidiClient/genPrpt
cog -r *.h *.cpp