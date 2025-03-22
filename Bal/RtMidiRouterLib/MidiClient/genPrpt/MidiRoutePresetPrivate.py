from property import create_prpt, PrptClass



ary = [
    create_prpt("QString", 'name'),
    create_prpt("QString", 'uuidPrivate'),
    create_prpt("bool", 'isEnabled'),
    create_prpt("PresetMidiControl *", 'midiControlOn', is_writable=False, init_val = "= new PresetMidiControl(PresetMidiControl::PresetMidiType::PRESET_ON,this)"),
    create_prpt("PresetMidiControl *", 'midiControlOff', is_writable=False, init_val = "= new PresetMidiControl(PresetMidiControl::PresetMidiType::PRESET_OFF,this)"),    
    create_prpt("PresetMidiControl *", 'midiControlToggle', is_writable=False, init_val = "= new PresetMidiControl(PresetMidiControl::PresetMidiType::PRESET_TOGGLE,this)"),
    create_prpt("PresetMidiControl *", 'midiControlSelect', is_writable=False, init_val = "= new PresetMidiControl(PresetMidiControl::PresetMidiType::PRESET_SELECT,this)"),
    create_prpt("QList<UserControl *>", 'userControls', is_list=True,  init_val = "= new QList<UserControl *>()"),
    create_prpt("QList<MidiRouteInput *>", 'midiRouteInputs', is_list=True,  init_val = "= new QList<MidiRouteInput *>()")
]

enumClasss = []

prptClass = PrptClass("MidiRoutePresetPrivate", ary, enumClasss)
