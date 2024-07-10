from property import Prpt, PrptClass, EnumClass


ary = []
p = Prpt("QString",'serverStatusText')
p.is_bindable = False
p.is_writable = True
p.is_notify = True
ary.append(p)
p = Prpt("ServerStatus",'serverStatus')
p.is_bindable = False
p.is_writable = True
p.is_notify = True
ary.append(p)


enumClasss = []
e = EnumClass("ServerStatus",
        ["STOPPED", "STARTING", "RUNNING", "FAILED"])
enumClasss.append(e)

classMidiClientConnectionPrivate = PrptClass("MidiClientConnectionPrivate", ary, enumClasss)
