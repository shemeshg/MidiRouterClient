

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

public slots:

private:
};
