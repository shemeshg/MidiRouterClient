//-define-file body GenHpp/MidiRouteInput.cpp
//-define-file header GenHpp/MidiRouteInput.h
//-only-file header //-
#pragma once
//- #include "../genPrpt/MidiRouteInputPrivate.h"
//-only-file body //-
//- #include "MidiRouteInput.h"
//-only-file null
#include "../genPrpt/MidiRouteInputPrivate.hpp"
//-only-file header




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

        setIgnoreTypesMidiSysex(true);
        setIgnoreTypesMidiTime( true);
        setIgnoreTypesMidiSense(true);
        setMidiRouteClockTimeSig( 4);
        setMidiRouteClockTimeSigDivBy(4);
        setMidiRouteClockFromSppPos(0);
        m_monitor = new Monitor(this);
        m_easyConfig = new EasyConfig(this);
        // Dummy DELETE
        clearMidiRouteInputCc14bit();        
    };


    //- {fn}
    void clearEasyConfigMidiRouterChains()
    //-only-file body
    {
        for (int i = m_midiRouterChains.size() - 1; i >= 0; --i) {
            if (m_midiRouterChains[i]->isEasyConfig()) {
                delMidiRouterChains(i);
            }
        }
    }

    //- {fn}
    void createEasyConfigChains(EasyConfig *easyConfig)
    //-only-file body
    {
        for (auto easyConfigRoute : easyConfig->easyConfigRoutes()) {
            MidiRouterChain *midiRouterChain = new MidiRouterChain();
            midiRouterChain->setEasyConfigChain(easyConfig, easyConfigRoute);


            addMidiRouterChains(midiRouterChain);
        }
    }

    //- {fn}
    void addMonitorEasyConfigIfRequired()
    //-only-file body
    {
        if (monitor()->isMonitored()){
            MidiRouterChain *midiRouterChain = new MidiRouterChain();
            midiRouterChain->addEasyConfigMonitor();
            addMidiRouterChains(midiRouterChain);
        }
    }

    //- {fn}
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

    //- {fn}
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
    //- {fn}
    void addMidiRouterChain(const QString name)
    //-only-file body
    {
        MidiRouterChain *midiRouterChain = new MidiRouterChain();
        midiRouterChain->setName(name);
        addMidiRouterChains(midiRouterChain);
    }

    //- {fn}
    void delMidiRouterChain(const int idx)
    //-only-file body
    {
        delMidiRouterChains(idx);
    }
    //- {fn}
    void clear14BitCc()
    //-only-file body
    {
        clearMidiRouteInputCc14bit();
    }

    //- {fn}
    void add14BitCc(int channel, int cc)
    //-only-file body
    {
        MidiRouteInputCc14bit *item = new MidiRouteInputCc14bit();
        item->setChannel(channel);
        item->setCc(cc);
        addMidiRouteInputCc14bit(item);
    }

    //-only-file header
private:

};
