# will be ver 2 of midi router

setup the python
```
python3 -m venv .venv
source .venv/bin/activate
pip install cogapp

```

cog qt headers
```
cd MidiRouterClient/Bal/RtMidiRouterLib/MidiClient
python -m cogapp -r *.h *.cpp
cog -h
```

ubuntu required packages
- `libasound2-dev`
