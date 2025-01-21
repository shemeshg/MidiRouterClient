from property import create_prpt, PrptClass



ary = [
    create_prpt("QList<int>", 'keyboardSplits',False),
    create_prpt("QStringList", 'zoneNames'),
    create_prpt("QList<EasyConfigRoute *>", 'easyConfigRoutes', is_list=True)
]

enumClasss = [
]

prptClass = PrptClass("EasyConfigPrivate", ary, enumClasss)
