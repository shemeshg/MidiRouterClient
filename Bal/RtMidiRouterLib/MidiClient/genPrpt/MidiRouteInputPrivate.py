from property import create_prpt, PrptClass



ary = [
    create_prpt("QString", 'uuid'),
    create_prpt("QString", 'midiInputName'),
    create_prpt("bool", 'ignoreTypesMidiSysex'),
    create_prpt("bool", 'ignoreTypesMidiTime'),
    create_prpt("bool", 'ignoreTypesMidiSense'),

    create_prpt("int", 'midiRouteClockTimeSig'),
    create_prpt("int", 'midiRouteClockTimeSigDivBy'),
    create_prpt("int", 'midiRouteClockFromSppPos'),
    create_prpt("QStringList", 'midiRouteClockPropegateInputs',  init_val = "= {}"),
    create_prpt("QList<MidiRouteInputCc14bit *>", 'midiRouteInputCc14bit', is_list=True,  init_val = "= {}"),
    create_prpt("QList<MidiRouterChain *>", 'midiRouterChains', is_list=True,  init_val = "= {}"),
    create_prpt("Monitor *", 'monitor', is_writable=False, init_val = "= new Monitor(this)"),
    create_prpt("EasyConfig *", 'easyConfig', is_writable=False, init_val = "= new EasyConfig()")
]

enumClasss = []

prptClass = PrptClass("MidiRouteInputPrivate", ary, enumClasss)
