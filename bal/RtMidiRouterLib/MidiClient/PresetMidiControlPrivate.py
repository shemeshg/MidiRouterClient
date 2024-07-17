from property import Prpt, PrptClass


ary = []
p = Prpt("QString",'portName')
p.is_bindable = False
p.is_writable = True
p.is_notify = True
ary.append(p)


enumClasss = []


classPresetMidiControlPrivate = PrptClass("PresetMidiControlPrivate", ary, enumClasss)
