#include "MidiRoutePreset.h"
     MidiRoutePreset::MidiRoutePreset(QString computerUuid, QObject * parent) 
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

    void MidiRoutePreset::recreateEasyConfig(QList<MidiPresetControlEasyConfig> &midiPresetControlEasyConfigs) 
    {
        for ( MidiRouteInput *input: m_midiRouteInputs){
            input->clearEasyConfigMidiRouterChains();
            input->addMonitorEasyConfigIfRequired();
            input->addMidiPresetControlEasyConfigsIfRequired(midiPresetControlEasyConfigs);
        }

        for (EasyConfig *easyConfig: m_easyConfig){
            auto const midiInputName = easyConfig->midiInputName();
            getInputOrCreateByName(midiInputName)->createEasyConfigChains(easyConfig);

        }
    }





    MidiRouteInput*  MidiRoutePreset::getInputOrCreateByName(QString midiInputName) 
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

    std::optional<MidiRouteInput *> MidiRoutePreset::getInputByName(QString midiInputName) 
    {
        for (MidiRouteInput *input : m_midiRouteInputs) {
            if (input->midiInputName() == midiInputName) {
                return input;
            }
        }

        return std::nullopt;
    }

