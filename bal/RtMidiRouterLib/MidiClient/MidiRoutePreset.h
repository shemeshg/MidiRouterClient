#pragma once
#include "EasyConfig.h"
#include "MidiClientUtil.h"
#include "MidiRoutePresetPrivate.h"

class MidiRoutePreset : public MidiRoutePresetPrivate

{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit MidiRoutePreset(QString computerUuid, QObject *parent = nullptr)
        : MidiRoutePresetPrivate{parent}{
        setComputerUuid(computerUuid);
        setUuid(getUuId());
        m_midiControlOn = new PresetMidiControl(
            PresetMidiControl::PresetMidiType::PRESET_ON,
            uuid());
        m_midiControlOff = new PresetMidiControl(
            PresetMidiControl::PresetMidiType::PRESET_OFF,
            uuid());

        clearEasyConfig();
    };

    void clearEasyConfig(){
        for (const EasyConfig *item : m_easyConfig) {
            delete item;
        }
        // Clear the outer list
        m_easyConfig.clear();
        emit easyConfigChanged();
    }
public slots:

signals:


private:

};
