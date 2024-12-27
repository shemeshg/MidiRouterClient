#include "PresetMidiControl.h"
     PresetMidiControl::PresetMidiControl(PresetMidiType presetMidiType, QString presetUuid, QObject * parent) 
        : PresetMidiControlPrivate{parent}
        {
            setPresetUuid(presetUuid);
            setPresetMidiType(presetMidiType);

        };

