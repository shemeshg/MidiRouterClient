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

    void clearMidiRouteInputs(){
        for (MidiRouteInput *item : m_midiRouteInputs) {
            delete item;
        }
        // Clear the outer list

        m_midiRouteInputs.clear();
        emit midiRouteInputsChanged();
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

    void recreateEasyConfig(){
        for ( MidiRouteInput *input: m_midiRouteInputs){
            input->clearEasyConfigMidiRouterChains();
            input->addMonitorEasyConfigIfRequired();
        }

        for (EasyConfig *easyConfig: m_easyConfig){
            auto const midiInputName = easyConfig->midiInputName();
            std::optional<MidiRouteInput*> input  = getInputForEasyConfig(midiInputName);
            if (!input){
                input = new MidiRouteInput();
                input.value()->setMidiInputName(midiInputName);
                addMidiRouteInput(input.value());
            }
            input.value()->createEasyConfigChains(easyConfig);

        }
    }

    void addUserControl( UserControl *entry ){
        m_userControls.push_back(entry);
        emit userControlsChanged();
    }

    void addEasyConfig( EasyConfig *entry ){
        m_easyConfig.push_back(entry);
        emit easyConfigChanged();
    }

    void addMidiRouteInput( MidiRouteInput *entry ){
        m_midiRouteInputs.push_back(entry);
        emit midiRouteInputsChanged();
    }

public slots:

signals:


private:
    std::optional<MidiRouteInput *> getInputForEasyConfig(QString midiInputName) {
        for (MidiRouteInput *input : m_midiRouteInputs) {
            if (input->midiInputName() == midiInputName) {
                return input;
            }
        }

        return std::nullopt;
    }
};
