from property import create_prpt, PrptClass



ary = [
   create_prpt("QString", 'name'),
   create_prpt("bool", 'isEasyConfig'),
   create_prpt("QList<QVariant>", 'midiRoutersFilters', is_writable=False)

]

enumClasss = [
]

classMidiRouterChainPrivate = PrptClass("MidiRouterChainPrivate", ary, enumClasss)
