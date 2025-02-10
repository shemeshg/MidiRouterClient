#line 7 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/PresetMidiControl.hpp"
#include "PresetMidiControl.h"
     PresetMidiControl::PresetMidiControl(PresetMidiType presetMidiType, QString presetUuid, QObject * parent) 
#line 25 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/PresetMidiControl.hpp"
        : PresetMidiControlPrivate{parent}
        {
            setPresetUuid(presetUuid);
            setPresetMidiType(presetMidiType);
            setChannel(-1);
            setData1(-1);
            setData2(-1);
        };

