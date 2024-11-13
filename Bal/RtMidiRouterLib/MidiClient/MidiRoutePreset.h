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
        clearUserControls();

    };

    void clearUserControls(){
        for (UserControl *item : m_userControls) {
            delete item;
        }
        // Clear the outer list

        m_userControls.clear();
        emit userControlsChanged();
    }
    void clearEasyConfig(){
        for (EasyConfig *item : m_easyConfig) {
            item->clearEasyConfigRoute();
            delete item;
        }
        // Clear the outer list

        m_easyConfig.clear();
        emit easyConfigChanged();
    }

    void addUserControl( UserControl *entry ){
        m_userControls.push_back(entry);
        emit userControlsChanged();
    }

    void addEasyConfig( EasyConfig *entry ){
        m_easyConfig.push_back(entry);
        emit easyConfigChanged();
    }
public slots:

signals:


private:

};
