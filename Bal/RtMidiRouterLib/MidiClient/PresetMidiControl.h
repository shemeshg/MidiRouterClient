

#pragma once

#include "genPrpt/PresetMidiControlPrivate.h"

class PresetMidiControl : public PresetMidiControlPrivate

{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit PresetMidiControl(PresetMidiType presetMidiType,
                               QString presetUuid,
                               QObject *parent = nullptr)
        : PresetMidiControlPrivate{parent}
        {
            setPresetUuid(presetUuid);
            setPresetMidiType(presetMidiType);

        };

public slots:

private:
};
