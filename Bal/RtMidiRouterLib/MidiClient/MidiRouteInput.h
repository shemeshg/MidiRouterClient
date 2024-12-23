

#pragma once
#include "EasyConfig.h"
#include "MidiRouteInputPrivate.h"
#include "MidiPresetControlEasyConfig.h"

class MidiRouteInput : public MidiRouteInputPrivate

{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit MidiRouteInput(QObject *parent = nullptr)
        : MidiRouteInputPrivate{parent} {
        clearMidiRouteInputCc14bit();
        clearMidiRouterChains();
    };



    void clearEasyConfigMidiRouterChains() {
        for (int i = m_midiRouterChains.size() - 1; i >= 0; --i) {
            if (m_midiRouterChains[i]->isEasyConfig()) {
                delMidiRouterChains(i);
            }
        }
    }

    void createEasyConfigChains(EasyConfig *easyConfig) {
        for (auto easyConfigRoute : easyConfig->easyConfigRoutes()) {
            MidiRouterChain *midiRouterChain = new MidiRouterChain();
            midiRouterChain->setEasyConfigChain(easyConfig, easyConfigRoute);


            addMidiRouterChains(midiRouterChain);
        }
    }

    void addMonitorEasyConfigIfRequired(){
        if (monitor()->isMonitored()){
            MidiRouterChain *midiRouterChain = new MidiRouterChain();
            midiRouterChain->addEasyConfigMonitor();
            addMidiRouterChains(midiRouterChain);
        }
    }

    void addMidiPresetControlEasyConfigsIfRequired(QList<MidiPresetControlEasyConfig> &midiPresetControlEasyConfigs){
        qDebug()<<"midiPresetControlEasyConfigs";
        for (const auto &m: midiPresetControlEasyConfigs){
            if (m.pmc->portName() == midiInputName()){
                MidiRouterChain *midiRouterChain = new MidiRouterChain();
                midiRouterChain->addEasyConfigPresetFilter(m);
                midiRouterChain->addEasyConfigPresetLogOnOff(m.pmc->presetUuid(), m.isMidiControlOn);
                addMidiRouterChains(midiRouterChain);
            }
        }
    }

    void clearMidiRouterChains() {
        for (MidiRouterChain *item : m_midiRouterChains) {
            delete item;
        }
        // Clear the outer list

        m_midiRouterChains.clear();
        emit midiRouterChainsChanged();
    }

public slots:

private:

};
