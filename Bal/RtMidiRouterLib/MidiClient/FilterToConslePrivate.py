from property import create_prpt, PrptClass, EnumClass



ary = [
    create_prpt("LogTo", 'logTo'),
    create_prpt("QString", 'userdata'),
]

enumClasss = [
    EnumClass("LogTo", ["CLIENT", "SERVER"])
]

classFilterToConslePrivate = PrptClass("FilterToConslePrivate", ary, enumClasss)
classFilterToConslePrivate.inhirit_from = "MidiRoutersFilter"
