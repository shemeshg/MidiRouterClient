from property import create_prpt, PrptClass



ary = [
    create_prpt("QString", 'name'),
    create_prpt("QString", 'uuid'),
    create_prpt("QString", 'computerUuid'),
    create_prpt("bool", 'isSendAllUserControls'),
    create_prpt("PresetMidiControl *", 'midiControlOn', is_writable=False),
    create_prpt("PresetMidiControl *", 'midiControlOff', is_writable=False)
]

enumClasss = []

classMidiRoutePresetPrivate = PrptClass("MidiRoutePresetPrivate", ary, enumClasss)
