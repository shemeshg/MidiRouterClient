from property import create_prpt, PrptClass



ary = [
   create_prpt("QString", 'name'),
   create_prpt("bool", 'isEasyConfig')
]

enumClasss = [
]

classMidiRouterChainPrivate = PrptClass("MidiRouterChainPrivate", ary, enumClasss)
