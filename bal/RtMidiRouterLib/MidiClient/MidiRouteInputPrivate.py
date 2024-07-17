from property import Prpt, PrptClass


ary = []
p = Prpt("QString",'name')
p.is_bindable = False
p.is_writable = True
p.is_notify = True
ary.append(p)


enumClasss = []


classMidiRouteInputPrivate = PrptClass("MidiRouteInputPrivate", ary, enumClasss)
