//-define-file body GenHpp/PresetMidiControl.cpp
//-define-file header GenHpp/PresetMidiControl.h
//-only-file header //-
//-only-file body //-
//- #include "PresetMidiControl.h"
//-only-file null
//-only-file header
#pragma once
#include "../genPrpt/PresetMidiControlPrivate.h"

//-var {PRE} "PresetMidiControl::"
class PresetMidiControl : public PresetMidiControlPrivate

{
    Q_OBJECT
    QML_ELEMENT
public:
    //- {function} 1 1
    explicit PresetMidiControl(PresetMidiType presetMidiType,
                               QString presetUuid,
                               QObject *parent = nullptr)
        //-only-file body
        : PresetMidiControlPrivate{parent}
        {
            setPresetUuid(presetUuid);
            setPresetMidiType(presetMidiType);
            setChannel(-1);
            setData1(-1);
            setData2(-1);
        };

        //-only-file header
public slots:

private:
};
