#include "PresetMidiControl.h"
     PresetMidiControl::PresetMidiControl(PresetMidiType presetMidiType, QString presetUuid, QObject * parent) 
        : PresetMidiControlPrivate{parent}
        {
            setPresetUuid(presetUuid);
            setPresetMidiType(presetMidiType);
            setChannel(-1);
            setData1(-1);
            setData2(-1);
        };

