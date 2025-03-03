from property import create_prpt, PrptClass



ary = [
    create_prpt("int", 'activePresetID'),
    create_prpt("QString", 'computerUuid', is_writable=False, is_notify=False),
    create_prpt("QList<Dropdownlist *>", 'dropdownlists', is_list=True),
    create_prpt("QString", 'uniqueId', is_writable=False),
    create_prpt("QStringList", 'virtualInPorts', is_writable=False),
    create_prpt("QList<MidiRoutePreset *>", 'midiRoutePresets', is_list=True),
    create_prpt("QStringList", 'connectedInPorts'),
    create_prpt("QStringList", 'connectedOutPorts'),
    create_prpt("MidiRoutePreset *", 'activePreset', is_writable=False),
    create_prpt("QString", 'criticalErrorMsg')
]

enumClasss = []

prptClass = PrptClass("UserDataConfigPrivate", ary, enumClasss)
