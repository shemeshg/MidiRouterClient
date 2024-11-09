from property import Prpt, PrptClass, EnumClass


ary = []
p = Prpt("QString",'portName')
p.is_bindable = False
p.is_writable = True
p.is_notify = True
ary.append(p)
p = Prpt("PresetMidiType",'presetMidiType')
p.is_bindable = False
p.is_writable = True
p.is_notify = True
ary.append(p)
p = Prpt("QString",'presetUuid')
p.is_bindable = False
p.is_writable = True
p.is_notify = True
ary.append(p)
p = Prpt("int",'eventTypeId')
p.is_bindable = False
p.is_writable = True
p.is_notify = True
ary.append(p)
p = Prpt("int",'channel')
p.is_bindable = False
p.is_writable = True
p.is_notify = True
ary.append(p)
p = Prpt("int",'data1')
p.is_bindable = False
p.is_writable = True
p.is_notify = True
ary.append(p)
p = Prpt("int",'data2')
p.is_bindable = False
p.is_writable = True
p.is_notify = True
ary.append(p)

enumClasss = []
e = EnumClass("PresetMidiType",
        ["PRESET_OFF", "PRESET_ON"])
enumClasss.append(e)

classPresetMidiControlPrivate = PrptClass("PresetMidiControlPrivate", ary, enumClasss)
