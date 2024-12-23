from property import create_prpt, PrptClass, EnumClass



ary = [
    create_prpt("LogTo", 'logTo'),
    create_prpt("QString", 'userdata'),
]

enumClasss = [
    EnumClass("LogTo", ["CLIENT", "SERVER"])
]

prptClass = PrptClass("FilterToConslePrivate", ary, enumClasss)
prptClass.inhirit_from = "MidiRoutersFilter"
