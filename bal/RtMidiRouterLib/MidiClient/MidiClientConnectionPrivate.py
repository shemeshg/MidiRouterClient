from property import create_prpt, PrptClass, EnumClass



ary = [
    create_prpt("QString", 'serverStatusText'),
    create_prpt("ServerStatus", 'serverStatus'),
    create_prpt("UserDataConfig *", 'userDataConfig', is_writable=False),
]

enumClasss = [
    EnumClass("ServerStatus", ["STOPPED", "STARTING", "RUNNING", "FAILED"])
]

classMidiClientConnectionPrivate = PrptClass("MidiClientConnectionPrivate", ary, enumClasss)
