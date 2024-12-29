#include "MidiRouteInput.h"
     MidiRouteInput::MidiRouteInput(QObject * parent) 
        : MidiRouteInputPrivate{parent} {
        clearMidiRouteInputCc14bit();
        clearMidiRouterChains();
        clearEasyConfig();

        setIgnoreTypesMidiSysex(true);
        setIgnoreTypesMidiTime( true);
        setIgnoreTypesMidiSense(true);
        setMidiRouteClockTimeSig( 4);
        setMidiRouteClockTimeSigDivBy(4);
        setMidiRouteClockFromSppPos(0);
        m_monitor = new Monitor(this);
        // Dummy DELETE
        clearMidiRouteInputCc14bit();
        add14BitCc(2, 5);
    };


    void MidiRouteInput::clearEasyConfigMidiRouterChains() 
    {
        for (int i = m_midiRouterChains.size() - 1; i >= 0; --i) {
            if (m_midiRouterChains[i]->isEasyConfig()) {
                delMidiRouterChains(i);
            }
        }
    }

    void MidiRouteInput::createEasyConfigChains(EasyConfig * easyConfig) 
    {
        for (auto easyConfigRoute : easyConfig->easyConfigRoutes()) {
            MidiRouterChain *midiRouterChain = new MidiRouterChain();
            midiRouterChain->setEasyConfigChain(easyConfig, easyConfigRoute);


            addMidiRouterChains(midiRouterChain);
        }
    }

    void MidiRouteInput::addMonitorEasyConfigIfRequired() 
    {
        if (monitor()->isMonitored()){
            MidiRouterChain *midiRouterChain = new MidiRouterChain();
            midiRouterChain->addEasyConfigMonitor();
            addMidiRouterChains(midiRouterChain);
        }
    }

    void MidiRouteInput::addMidiPresetControlEasyConfigsIfRequired(QList<MidiPresetControlEasyConfig> &midiPresetControlEasyConfigs) 
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

    void MidiRouteInput::clearMidiRouterChains() 
    {
        for (MidiRouterChain *item : m_midiRouterChains) {
            delete item;
        }
        // Clear the outer list

        m_midiRouterChains.clear();
        emit midiRouterChainsChanged();
    }

    void MidiRouteInput::clear14BitCc() 
    {
        clearMidiRouteInputCc14bit();
    }

    void MidiRouteInput::add14BitCc(int channel, int cc) 
    {
        MidiRouteInputCc14bit *item = new MidiRouteInputCc14bit();
        item->setChannel(channel);
        item->setCc(cc);
        addMidiRouteInputCc14bit(item);
    }

