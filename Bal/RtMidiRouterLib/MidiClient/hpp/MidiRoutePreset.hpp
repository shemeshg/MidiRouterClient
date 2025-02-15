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

    //- {fn}
    void recreateEasyConfig(QList<MidiPresetControlEasyConfig> &midiPresetControlEasyConfigs)
    //-only-file body
    {
        for ( MidiRouteInput *input: m_midiRouteInputs){

            input->clearEasyConfigMidiRouterChains();
            input->addMonitorEasyConfigIfRequired();
            input->addMidiPresetControlEasyConfigsIfRequired(midiPresetControlEasyConfigs);


            getInputOrCreateByName(input->midiInputName())->createEasyConfigChains(input->easyConfig());

        }

    }





    //-only-file header
public slots:
     //- {fn}
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

     //- {fn}
     void addUserControl()
     //-only-file body
     {
         auto uc  = new UserControl();
         uc->setDescription("Description");
         uc->setMaxVal(127);
         uc->setDropdownListId(-1);
         addUserControls(uc);
     }


     //- {fn}
     void delUserControl(int id)
     //-only-file body
     {
         delUserControls(id);
     }


     //- {fn}
     void sendAllUserControls()
     //-only-file body
     {
         qDebug()<<"Not Implemented";
     }

    //-only-file header
signals:


private:


    //- {fn}
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
