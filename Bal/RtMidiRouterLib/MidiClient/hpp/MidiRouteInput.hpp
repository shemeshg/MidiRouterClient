//-define-file body GenHpp/MidiRouteInput.cpp
//-define-file header GenHpp/MidiRouteInput.h
//-only-file header //-
#pragma once
//- #include "../genPrpt/MidiRouteInputPrivate.h"
//- #include "MidiClientUtil.h"
//-only-file body //-
//- #include "MidiRouteInput.h"
//-only-file null
#include "../genPrpt/MidiRouteInputPrivate.hpp"
#include "MidiClientUtil.hpp"
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
        clearList<MidiRouteInputCc14bit *>();
        clearMidiRouterChains();

        setIgnoreTypesMidiSysex(true);
        setIgnoreTypesMidiTime( true);
        setIgnoreTypesMidiSense(true);
        setMidiRouteClockTimeSig( 4);
        setMidiRouteClockTimeSigDivBy(4);
        setMidiRouteClockFromSppPos(0);
        m_monitor = new Monitor(this);
        m_easyConfig = new EasyConfig(this);
        setUuid(getUuId());
    };


    //- {fn}
    void clearEasyConfigMidiRouterChains()
    //-only-file body
    {
        for (int i = m_midiRouterChains.size() - 1; i >= 0; --i) {
            if (m_midiRouterChains[i]->isEasyConfig()) {
                delListItem<MidiRouterChain *>(i);
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


            addListItem(midiRouterChain);
        }
    }

    //- {fn}
    void addMonitorEasyConfigIfRequired()
    //-only-file body
    {
        if (monitor()->isMonitored()){
            MidiRouterChain *midiRouterChain = new MidiRouterChain();
            midiRouterChain->addEasyConfigMonitor();
            addListItem(midiRouterChain);
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
                addListItem(midiRouterChain);
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
        addListItem(midiRouterChain);
    }

    //- {fn}
    void delMidiRouterChain(const int idx)
    //-only-file body
    {
        delListItem<MidiRouterChain *>(idx);
    }
    //- {fn}
    void clear14BitCc()
    //-only-file body
    {
        clearList<MidiRouteInputCc14bit *>();
    }

    //- {fn}
    void add14BitCc(int channel, int cc)
    //-only-file body
    {
        MidiRouteInputCc14bit *item = new MidiRouteInputCc14bit();
        item->setChannel(channel);
        item->setCc(cc);
        addListItem(item);
    }

    //-only-file header
private:

};
