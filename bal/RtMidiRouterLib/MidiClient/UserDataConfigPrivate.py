from property import Prpt, PrptClass


ary = []
p = Prpt("int",'activePresetID')
p.is_bindable = False
p.is_writable = True
p.is_notify = True
ary.append(p)

enumClasss = []


classUserDataConfigPrivate = PrptClass("UserDataConfigPrivate", ary, enumClasss)
