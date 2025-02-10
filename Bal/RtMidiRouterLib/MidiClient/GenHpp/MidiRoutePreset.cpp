#line 8 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/MidiRoutePreset.hpp"
#include "MidiRoutePreset.h"
     MidiRoutePreset::MidiRoutePreset(QString computerUuid, QObject * parent) 
#line 25 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/MidiRoutePreset.hpp"
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

    void MidiRoutePreset::recreateEasyConfig(QList<MidiPresetControlEasyConfig> &midiPresetControlEasyConfigs) 
#line 42 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/MidiRoutePreset.hpp"
    {
        for ( MidiRouteInput *input: m_midiRouteInputs){

            input->clearEasyConfigMidiRouterChains();
            input->addMonitorEasyConfigIfRequired();
            input->addMidiPresetControlEasyConfigsIfRequired(midiPresetControlEasyConfigs);


            getInputOrCreateByName(input->midiInputName())->createEasyConfigChains(input->easyConfig());

        }

    }





    MidiRouteInput*  MidiRoutePreset::getInputOrCreateByName(QString midiInputName) 
#line 65 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/MidiRoutePreset.hpp"
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

    void MidiRoutePreset::addUserControl() 
#line 79 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/MidiRoutePreset.hpp"
     {
         auto uc  = new UserControl();
         uc->setDescription("Description");
         uc->setMaxVal(127);
         uc->setDropdownListId(-1);
         addUserControls(uc);
     }


    void MidiRoutePreset::delUserControl(int id) 
#line 91 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/MidiRoutePreset.hpp"
     {
         delUserControls(id);
     }


    void MidiRoutePreset::sendAllUserControls() 
#line 99 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/MidiRoutePreset.hpp"
     {
         qDebug()<<"Not Implemented";
     }

    std::optional<MidiRouteInput *> MidiRoutePreset::getInputByName(QString midiInputName) 
#line 113 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/MidiRoutePreset.hpp"
    {
        for (MidiRouteInput *input : m_midiRouteInputs) {
            if (input->midiInputName() == midiInputName) {
                return input;
            }
        }

        return std::nullopt;
    }

