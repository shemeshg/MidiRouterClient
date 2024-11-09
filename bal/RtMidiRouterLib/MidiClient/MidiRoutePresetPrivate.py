from property import Prpt, PrptClass


ary = []
p = Prpt("QString",'name')
p.is_bindable = False
p.is_writable = True
p.is_notify = True
ary.append(p)
p = Prpt("QString",'uuid')
p.is_bindable = False
p.is_writable = True
p.is_notify = True
ary.append(p)
p = Prpt("QString",'computerUuid')
p.is_bindable = False
p.is_writable = True
p.is_notify = True
ary.append(p)
p = Prpt("bool",'isSendAllUserControls')
p.is_bindable = False
p.is_writable = True
p.is_notify = True
ary.append(p)

p = Prpt("PresetMidiControl *",'midiControlOn')
p.is_bindable = False
p.is_writable = False
p.is_notify = True
ary.append(p)
p = Prpt("PresetMidiControl *",'midiControlOff')
p.is_bindable = False
p.is_writable = False
p.is_notify = True
ary.append(p)


enumClasss = []


classMidiRoutePresetPrivate = PrptClass("MidiRoutePresetPrivate", ary, enumClasss)
