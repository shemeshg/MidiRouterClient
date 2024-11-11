from property import create_prpt, PrptClass, EnumClass



ary = [
    create_prpt("QString", 'portName'),
    create_prpt("PresetMidiType", 'presetMidiType'),
    create_prpt("QString", 'presetUuid'),
    create_prpt("int", 'eventTypeId'),
    create_prpt("int", 'channel'),
    create_prpt("int", 'data1'),
    create_prpt("int", 'data2')
]

enumClasss = [
    EnumClass("PresetMidiType", ["PRESET_OFF", "PRESET_ON"])
]

classPresetMidiControlPrivate = PrptClass("PresetMidiControlPrivate", ary, enumClasss)
