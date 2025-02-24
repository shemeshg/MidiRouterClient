from property import create_prpt, PrptClass



ary = [
    create_prpt("QString", 'name'),
    create_prpt("QString", 'uuid'), 
    create_prpt("bool", 'isEnabled'),
    create_prpt("PresetMidiControl *", 'midiControlOn', is_writable=False),
    create_prpt("PresetMidiControl *", 'midiControlOff', is_writable=False),    
    create_prpt("QList<UserControl *>", 'userControls', is_list=True),
    create_prpt("QList<MidiRouteInput *>", 'midiRouteInputs', is_list=True)
]

enumClasss = []

prptClass = PrptClass("MidiRoutePresetPrivate", ary, enumClasss)
