from property import Prpt, PrptClass


ary = []
p = Prpt("int",'activePresetID')
p.is_bindable = False
p.is_writable = True
p.is_notify = True
ary.append(p)
p = Prpt("QString",'computerUuid')
p.is_bindable = False
p.is_writable = False
p.is_notify = False
ary.append(p)

enumClasss = []


classUserDataConfigPrivate = PrptClass("UserDataConfigPrivate", ary, enumClasss)
