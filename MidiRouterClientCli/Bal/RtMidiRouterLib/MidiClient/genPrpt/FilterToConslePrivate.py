from property import create_prpt, PrptClass, EnumClass



ary = [
    create_prpt("LogTo", 'logTo',init_val="= LogTo::CLIENT"),
    create_prpt("QString", 'userdata'),
]

enumClasss = [
    EnumClass("LogTo", ["CLIENT", "SERVER"])
]

prptClass = PrptClass("FilterToConslePrivate", ary, enumClasss)
prptClass.inhirit_from = "MidiRoutersFilter"
