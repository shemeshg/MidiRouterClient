from property import create_prpt, PrptClass



ary = [
    create_prpt("int", 'splitRangeId'),
    create_prpt("int", 'fromSelectedMidiEventTypeId'),
    create_prpt("int", 'fromChannel'),
    create_prpt("int", 'fromData1'),
    create_prpt("int", 'transpose'),
    create_prpt("int", 'fromCcOrNrpnStart'),
    create_prpt("int", 'fromCcOrNrpnEnd'),
    create_prpt("int", 'toCcOrNrpnStart'),
    create_prpt("int", 'toCcOrNrpnEnd'),
    create_prpt("int", 'toSelectedMidiEventTypeId'),
    create_prpt("int", 'toChannel'),
    create_prpt("int", 'toData1'),
    create_prpt("QString", 'toDestinationName'),
]

enumClasss = [
]

prptClass = PrptClass("EasyConfigRoutePrivate", ary, enumClasss)
