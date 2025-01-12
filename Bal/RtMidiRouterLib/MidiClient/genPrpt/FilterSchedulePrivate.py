from property import create_prpt, PrptClass, EnumClass



ary = [
    create_prpt("DefferedType", 'defferedType'),
    create_prpt("int", 'defferedTo'),
]

enumClasss = [
    EnumClass("DefferedType", ["IN_SPP",
        "IN_BAR",
        "AT_SPP" ,
        "AT_BAR",
        "QUANTIZE_SPP",
        "QUANTIZE_BAR"])
]

prptClass = PrptClass("FilterSchedulePrivate", ary, enumClasss)
prptClass.inhirit_from = "MidiRoutersFilter"
