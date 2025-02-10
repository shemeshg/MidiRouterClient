#pragma once
#include "../genPrpt/PresetMidiControlPrivate.h"


class PresetMidiControl : public PresetMidiControlPrivate

{
    Q_OBJECT
    QML_ELEMENT
public:
#line 21 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/PresetMidiControl.hpp"
    explicit PresetMidiControl(PresetMidiType presetMidiType,
                               QString presetUuid,
                               QObject *parent = nullptr);
public slots:

private:
};
