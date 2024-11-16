

#pragma once
#include "MidiRouteInputPrivate.h"

class MidiRouteInput : public MidiRouteInputPrivate

{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit MidiRouteInput(QObject *parent = nullptr)
        : MidiRouteInputPrivate{parent} {
        clearMidiRouteInputCc14bit();
        clearMidiRouterChain();
    };

    void addMidiRouteInputCc14bit( MidiRouteInputCc14bit *entry ){
        m_midiRouteInputCc14bit.push_back(entry);
        emit midiRouteInputCc14bitChanged();
    }

    void clearMidiRouteInputCc14bit(){
        for (MidiRouteInputCc14bit *item : m_midiRouteInputCc14bit) {
            delete item;
        }
        // Clear the outer list

        m_midiRouteInputCc14bit.clear();
        emit midiRouteInputCc14bitChanged();
    }

    void addMidiRouterChains( MidiRouterChain *entry ){
        m_midiRouterChains.push_back(entry);
        emit midiRouterChainsChanged();
    }

    void clearMidiRouterChain(){
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
