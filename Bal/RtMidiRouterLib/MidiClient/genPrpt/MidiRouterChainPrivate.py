from property import create_prpt, PrptClass



ary = [
   create_prpt("QString", 'name'),
   create_prpt("QString", 'uuid'),
   create_prpt("bool", 'isEasyConfig'),
   create_prpt("bool", 'isRunForPresetOnAndOff'),
   # it is not is_list for a good reason
   create_prpt("QList<QVariant>", 'midiRoutersFilters', is_writable=False)

]

enumClasss = [
]

prptClass = PrptClass("MidiRouterChainPrivate", ary, enumClasss)
