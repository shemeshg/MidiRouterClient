from property import create_prpt, PrptClass



ary = [
    create_prpt("QString", 'midiInputName'),
    create_prpt("bool", 'ignoreTypesMidiSysex'),
    create_prpt("bool", 'ignoreTypesMidiTime'),
    create_prpt("bool", 'ignoreTypesMidiSense'),

    create_prpt("int", 'midiRouteClockTimeSig'),
    create_prpt("int", 'midiRouteClockTimeSigDivBy'),
    create_prpt("int", 'midiRouteClockFromSppPos'),
    create_prpt("QStringList", 'midiRouteClockPropegateInputs'),
    create_prpt("QList<MidiRouteInputCc14bit *>", 'midiRouteInputCc14bit', is_writable=False),
    create_prpt("QList<MidiRouterChain *>", 'midiRouterChains', is_writable=False)
]

enumClasss = []

classMidiRouteInputPrivate = PrptClass("MidiRouteInputPrivate", ary, enumClasss)
