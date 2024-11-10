from property import Prpt, PrptClass

def create_prpt(type_name, name, is_writable=True, is_notify=True):
    p = Prpt(type_name, name)
    p.is_bindable = False
    p.is_writable = is_writable
    p.is_notify = is_notify
    return p

ary = [
    create_prpt("int", 'activePresetID'),
    create_prpt("QString", 'computerUuid', is_writable=False, is_notify=False),
    create_prpt("QList<Dropdownlist *>", 'dropdownlists', is_writable=False),
    create_prpt("QString", 'uniqueId', is_writable=False),
    create_prpt("QStringList", 'virtualInPorts', is_writable=False),
    create_prpt("QList<MidiRoutePreset *>", 'midiRoutePresets', is_writable=False)
]

enumClasss = []

classUserDataConfigPrivate = PrptClass("UserDataConfigPrivate", ary, enumClasss)
