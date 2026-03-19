from property import create_prpt, PrptClass



ary = [
    create_prpt("QList<int>", 'keyboardSplits',False, init_val = "={}"),
    create_prpt("QStringList", 'zoneNames', init_val = "={}"),
    create_prpt("QList<EasyConfigRoute *>", 'easyConfigRoutes', is_list=True, init_val = "= new QList<EasyConfigRoute *>()")
]

enumClasss = [
]

prptClass = PrptClass("EasyConfigPrivate", ary, enumClasss)
