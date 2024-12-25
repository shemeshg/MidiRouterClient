#pragma once
#include "GenHpp/EasyConfig.h"
#include "GenHpp/MidiClientUtil.h"
#include "genPrpt/MidiRoutePresetPrivate.h"
#include "GenHpp/MidiPresetControlEasyConfig.h"

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
            uuid(),this);
        m_midiControlOff = new PresetMidiControl(
            PresetMidiControl::PresetMidiType::PRESET_OFF,
            uuid(),this);

        clearEasyConfig();
        clearUserControls();

    };


    void recreateEasyConfig(QList<MidiPresetControlEasyConfig> &midiPresetControlEasyConfigs){
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
