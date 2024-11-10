from property import Prpt, PrptClass

def create_prpt(type_name, name, is_writable=True):
    p = Prpt(type_name, name)
    p.is_bindable = False
    p.is_writable = is_writable
    p.is_notify = True
    return p

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
