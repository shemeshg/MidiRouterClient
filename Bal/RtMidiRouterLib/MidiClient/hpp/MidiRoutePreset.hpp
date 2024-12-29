//-define-file body GenHpp/MidiRoutePreset.cpp
//-define-file header GenHpp/MidiRoutePreset.h
//-only-file header //-
#pragma once
//- #include "../genPrpt/MidiRoutePresetPrivate.h"
//- #include "MidiClientUtil.h"
//-only-file body //-
//- #include "MidiRoutePreset.h"
//-only-file null
#include "MidiClientUtil.hpp"
#include "../genPrpt/MidiRoutePresetPrivate.hpp"
//-only-file header


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

        clearUserControls();

    };

    //- {function} 0 1
    void recreateEasyConfig(QList<MidiPresetControlEasyConfig> &midiPresetControlEasyConfigs)
    //-only-file body
    {
        for ( MidiRouteInput *input: m_midiRouteInputs){
            input->clearEasyConfig();
            input->clearEasyConfigMidiRouterChains();
            input->addMonitorEasyConfigIfRequired();
            input->addMidiPresetControlEasyConfigsIfRequired(midiPresetControlEasyConfigs);

            for (EasyConfig *easyConfig: input->easyConfig()){
                getInputOrCreateByName(input->midiInputName())->createEasyConfigChains(easyConfig);
            }
        }

    }





    //-only-file header
public slots:
     //- {function} 0 1
     MidiRouteInput* getInputOrCreateByName(QString midiInputName)
     //-only-file body
     {
        std::optional<MidiRouteInput *> input = getInputByName(midiInputName);
         if (input){
             return input.value();
         }
         MidiRouteInput *newInput = new MidiRouteInput();
         newInput->setMidiInputName(midiInputName);
         addMidiRouteInputs(newInput);
         return newInput;
     }

    //-only-file header
signals:


private:


    //- {function} 0 1
    std::optional<MidiRouteInput *> getInputByName(QString midiInputName) 
    //-only-file body
    {
        for (MidiRouteInput *input : m_midiRouteInputs) {
            if (input->midiInputName() == midiInputName) {
                return input;
            }
        }

        return std::nullopt;
    }

    //-only-file header
};
