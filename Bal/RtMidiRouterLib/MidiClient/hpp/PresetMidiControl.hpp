//-define-file body GenHpp/PresetMidiControl.cpp
//-define-file header GenHpp/PresetMidiControl.h
//-only-file header //-
#pragma once
#include <QJsonObject>
//- #include "../genPrpt/PresetMidiControlPrivate.h"
//-only-file body //-
//- #include "PresetMidiControl.h"
//-only-file null
#include "../genPrpt/PresetMidiControlPrivate.hpp"
//-only-file header


//-var {PRE} "PresetMidiControl::"
class PresetMidiControl : public PresetMidiControlPrivate

{
    Q_OBJECT
    QML_ELEMENT
public:
    //- {function} 1 1
    explicit PresetMidiControl(PresetMidiType presetMidiType,                               
                               QObject *parent = nullptr)
        //-only-file body
        : PresetMidiControlPrivate{parent}
        {            
            setPresetMidiType(presetMidiType);
            setEventTypeId(0);
            setChannel(-1);
            setData1(-1);
            setData2(-1);
        };

        //- {fn}
        QJsonObject genJson()
        //-only-file body
        {
            QJsonObject obj;
            obj["presetMidiType"] = static_cast<int>(presetMidiType());
            obj["portName"] = portName();
            obj["eventTypeId"] = eventTypeId();
            obj["channel"] = channel();
            obj["data1"] = data1();
            obj["data2"] = data2();
            return obj;
        }

        //-only-file header
public slots:

private:
};
