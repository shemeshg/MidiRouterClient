from property import create_prpt, PrptClass, EnumClass



ary = [
    create_prpt("DefferedType", 'defferedType'),
    create_prpt("int", 'defferedTo'),
]

enumClasss = [
    EnumClass("DefferedType", ["IN_SPP",
        "IN_BAR",
        "AT_SPP_AT_BAR",
        "QUANTIZE_SPP",
        "QUANTIZE_BAR"])
]

classFilterSchedulePrivate = PrptClass("FilterSchedulePrivate", ary, enumClasss)
classFilterSchedulePrivate.inhirit_from = "MidiRoutersFilter"
