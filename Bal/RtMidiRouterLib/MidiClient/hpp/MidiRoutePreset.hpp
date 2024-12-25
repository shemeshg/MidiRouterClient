//-define-file body GenHpp/MidiRoutePreset.cpp
//-define-file header GenHpp/MidiRoutePreset.h
//-only-file header //-
#pragma once
//- #include "MidiClientUtil.h"
//-only-file body //-
//- #include "MidiRoutePreset.h"
//-only-file null
#include "MidiClientUtil.hpp"
//-only-file header
#include "../genPrpt/MidiRoutePresetPrivate.h"

//-var {PRE} "MidiRoutePreset::"
class MidiRoutePreset : public MidiRoutePresetPrivate

{
    Q_OBJECT
    QML_ELEMENT
public:
    //- {function} 1 1
    explicit MidiRoutePreset(QString computerUuid, QObject *parent = nullptr)
        //-only-file body
        : MidiRoutePresetPrivate{parent}{
        setComputerUuid(computerUuid);
        setUuid(getUuId());
        m_midiControlOn = new PresetMidiControl(
            PresetMidiControl::PresetMidiType::PRESET_ON,
            uuid(),this);
        m_midiControlOff = new PresetMidiControl(
            PresetMidiControl::PresetMidiType::PRESET_OFF,
            uuid(),this);

        clearEasyConfig();
        clearUserControls();

    };

    //- {function} 0 1
    void recreateEasyConfig(QList<MidiPresetControlEasyConfig> &midiPresetControlEasyConfigs)
    //-only-file body
    {
        for ( MidiRouteInput *input: m_midiRouteInputs){
            input->clearEasyConfigMidiRouterChains();
            input->addMonitorEasyConfigIfRequired();
            input->addMidiPresetControlEasyConfigsIfRequired(midiPresetControlEasyConfigs);
        }

        for (EasyConfig *easyConfig: m_easyConfig){
            auto const midiInputName = easyConfig->midiInputName();
            std::optional<MidiRouteInput*> input  = getInputByName(midiInputName);
            if (!input){
                input = new MidiRouteInput();
                input.value()->setMidiInputName(midiInputName);
                addMidiRouteInputs(input.value());
            }
            input.value()->createEasyConfigChains(easyConfig);

        }
    }





    //-only-file header
public slots:

signals:


private:
    std::optional<MidiRouteInput *> getInputByName(QString midiInputName) {
        for (MidiRouteInput *input : m_midiRouteInputs) {
            if (input->midiInputName() == midiInputName) {
                return input;
            }
        }

        return std::nullopt;
    }
};
