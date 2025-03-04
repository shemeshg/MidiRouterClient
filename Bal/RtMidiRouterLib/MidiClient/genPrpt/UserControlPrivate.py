from property import create_prpt, PrptClass, EnumClass



ary = [
    create_prpt("QString", 'uuid'),
    create_prpt("bool", 'isSendOnPresetChange'),
    create_prpt("EventType", 'eventType'),
    create_prpt("QString", 'description'),
    create_prpt("int", 'inputVal'),
    create_prpt("int", 'minVal'),
    create_prpt("int", 'maxVal'),
    create_prpt("bool", 'is64Mode'),
    create_prpt("int", 'channelId'),
    create_prpt("int", 'ccId'),
    create_prpt("int", 'nrpnControl'),
    create_prpt("QString", 'outputPortnName'),        
    create_prpt("bool", 'isShowDropdown'),
    create_prpt("int", 'dropdownListId'),
]

enumClasss = [
    EnumClass("EventType", ["CC", "PROGRAM_CHANGE","NRPN"])
]

prptClass = PrptClass("UserControlPrivate", ary, enumClasss)
