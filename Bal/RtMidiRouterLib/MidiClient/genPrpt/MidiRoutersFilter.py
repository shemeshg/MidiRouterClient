from property import create_prpt, PrptClass, EnumClass



ary = [
    create_prpt("QString", 'uuid'),
    create_prpt("FilterType", 'filterType', init_val = "= FilterType::TO_MIDI_DESTINATION"),
    create_prpt("QString", 'name'),
]

enumClasss = [
    EnumClass("FilterType", [
    "TO_MIDI_DESTINATION",
    "TO_CONSOLE",
    "TO_NETWORK",
    "SCHEDULE_TO",
    "FILTER_AND_TRANSFORM"])
]


prptClass = PrptClass("MidiRoutersFilter", ary, enumClasss)

