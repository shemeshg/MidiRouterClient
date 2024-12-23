from property import create_prpt, PrptClass



ary = [
    create_prpt("QString", 'midiInputName'),
    create_prpt("QList<int>", 'keyboardSplits'),
    create_prpt("QStringList", 'zoneNames'),
    create_prpt("QList<EasyConfigRoute *>", 'easyConfigRoutes', is_list=True),

]

enumClasss = [
]

classEasyConfigPrivate = PrptClass("EasyConfigPrivate", ary, enumClasss)
