

#pragma once
#include "EasyConfig.h"
#include "MidiRouteInputPrivate.h"

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

    void addMidiRouteInputCc14bit(MidiRouteInputCc14bit *entry) {
        m_midiRouteInputCc14bit.push_back(entry);
        emit midiRouteInputCc14bitChanged();
    }

    void clearMidiRouteInputCc14bit() {
        for (MidiRouteInputCc14bit *item : m_midiRouteInputCc14bit) {
            delete item;
        }
        // Clear the outer list

        m_midiRouteInputCc14bit.clear();
        emit midiRouteInputCc14bitChanged();
    }

    void addMidiRouterChains(MidiRouterChain *entry) {
        m_midiRouterChains.push_back(entry);
        emit midiRouterChainsChanged();
    }

    void clearEasyConfigMidiRouterChains() {
        for (int i = m_midiRouterChains.size() - 1; i >= 0; --i) {
            if (m_midiRouterChains[i]->isEasyConfig()) {
                delete m_midiRouterChains[i];
                m_midiRouterChains.removeAt(i);
            }
        }
        emit midiRouterChainsChanged();
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
