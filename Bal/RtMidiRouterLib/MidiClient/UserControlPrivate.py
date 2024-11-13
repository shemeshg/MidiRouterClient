from property import create_prpt, PrptClass, EnumClass



ary = [
    create_prpt("EventType", 'eventType'),
    create_prpt("QString", 'description'),
    create_prpt("int", 'inputVal'),
    create_prpt("int", 'minVal'),
    create_prpt("int", 'maxVal'),
    create_prpt("bool", 'is64Mode'),
    create_prpt("bool", 'isEditMode'),
    create_prpt("int", 'channelId'),
    create_prpt("int", 'ccId'),
    create_prpt("int", 'nrpnControl'),
    create_prpt("QString", 'outputPortnName'),
]

enumClasss = [
    EnumClass("EventType", ["CC", "PROGRAM_CHANGE","NRPN"])
]

classUserControlPrivate = PrptClass("EasyConfigRoutePrivate", ary, enumClasss)
