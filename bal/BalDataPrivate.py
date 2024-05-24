from property import Prpt, PrptClass, EnumClass
from lclStor import LclStor


ary = []

p = Prpt("int",'x')
p.is_bindable = False
p.is_writable = True
p.is_notify = True

p.is_local_storage = True
p.local_storage_default = 100
ary.append(p)
p = Prpt("int",'y')
p.is_bindable = False
p.is_writable = True
p.is_notify = True

p.is_local_storage = True
p.local_storage_default = 100
ary.append(p)
p = Prpt("int",'width')
p.is_bindable = False
p.is_writable = True
p.is_notify = True

p.is_local_storage = True
p.local_storage_default = 800
ary.append(p)
p = Prpt("int",'height')
p.is_bindable = False
p.is_writable = True
p.is_notify = True

p.is_local_storage = True
p.local_storage_default = 500
ary.append(p)



p = Prpt("int",'serverPort')
p.is_bindable = False
p.is_writable = False
p.is_notify = True
ary.append(p)

p = Prpt("bool",'isServerRunning')
p.is_bindable = False
p.is_writable = False
p.is_notify = True
ary.append(p)



enumClasss = []

classBalDataPrivate = PrptClass("BalDataPrivate", ary, enumClasss)
classBalDataPrivate.inhirit_from = "JsAsync"


localStore = LclStor(ary)    
