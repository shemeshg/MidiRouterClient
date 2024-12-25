//-define-file body GenHpp/MidiRouteInput.cpp
//-define-file header GenHpp/MidiRouteInput.h
//-only-file header //-
#pragma once
//-only-file body //-
//- #include "MidiRouteInput.h"
//-only-file null
//-only-file header

#include "../genPrpt/MidiRouteInputPrivate.h"


//-var {PRE} "MidiRouteInput::"
class MidiRouteInput : public MidiRouteInputPrivate

{
    Q_OBJECT
    QML_ELEMENT
public:
    //- {function} 1 1
    explicit MidiRouteInput(QObject *parent = nullptr)
        //-only-file body
        : MidiRouteInputPrivate{parent} {
        clearMidiRouteInputCc14bit();
        clearMidiRouterChains();
    };


    //- {function} 0 1
    void clearEasyConfigMidiRouterChains()
    //-only-file body
    {
        for (int i = m_midiRouterChains.size() - 1; i >= 0; --i) {
            if (m_midiRouterChains[i]->isEasyConfig()) {
                delMidiRouterChains(i);
            }
        }
    }

    //- {function} 0 1
    void createEasyConfigChains(EasyConfig *easyConfig)
    //-only-file body
    {
        for (auto easyConfigRoute : easyConfig->easyConfigRoutes()) {
            MidiRouterChain *midiRouterChain = new MidiRouterChain();
            midiRouterChain->setEasyConfigChain(easyConfig, easyConfigRoute);


            addMidiRouterChains(midiRouterChain);
        }
    }

    //- {function} 0 1
    void addMonitorEasyConfigIfRequired()
    //-only-file body
    {
        if (monitor()->isMonitored()){
            MidiRouterChain *midiRouterChain = new MidiRouterChain();
            midiRouterChain->addEasyConfigMonitor();
            addMidiRouterChains(midiRouterChain);
        }
    }

    //- {function} 0 1
    void addMidiPresetControlEasyConfigsIfRequired(QList<MidiPresetControlEasyConfig> &midiPresetControlEasyConfigs)
    //-only-file body
    {
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

    //- {function} 0 1
    void clearMidiRouterChains()
    //-only-file body
    {
        for (MidiRouterChain *item : m_midiRouterChains) {
            delete item;
        }
        // Clear the outer list

        m_midiRouterChains.clear();
        emit midiRouterChainsChanged();
    }

    //-only-file header
public slots:

private:

};
