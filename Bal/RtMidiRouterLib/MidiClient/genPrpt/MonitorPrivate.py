from property import create_prpt, PrptClass



ary = [
    create_prpt("bool", 'isMonitored'),
    create_prpt("QStringList", 'logItems', init_val = "= {}"),
    create_prpt("int", 'logLen'),
]

enumClasss = [
]

prptClass = PrptClass("MonitorPrivate", ary, enumClasss)
