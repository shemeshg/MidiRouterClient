from property import create_prpt, PrptClass, EnumClass



ary = [
    create_prpt("FilterType", 'filterType'),
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

