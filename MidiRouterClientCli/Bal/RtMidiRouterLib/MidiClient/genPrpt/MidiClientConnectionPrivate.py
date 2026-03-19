from property import create_prpt, PrptClass, EnumClass



ary = [
    create_prpt("QString", 'serverStatusText'),
    create_prpt("ServerStatus", 'serverStatus', init_val="= ServerStatus::STOPPED"),
    create_prpt("UserDataConfig *", 'userDataConfig', is_writable=False, init_val = "= new UserDataConfig(this);"),
]

enumClasss = [
    EnumClass("ServerStatus", ["STOPPED", "STARTING", "RUNNING", "FAILED"])
]

prptClass = PrptClass("MidiClientConnectionPrivate", ary, enumClasss)
