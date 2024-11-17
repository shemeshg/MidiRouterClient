#pragma once
#include "FilterMidiDestination.h"
#include "MidiRouterChainPrivate.h"
#include "MidiRoutersFilter.h"


class MidiRouterChain : public MidiRouterChainPrivate

{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit MidiRouterChain(QObject *parent = nullptr)
        : MidiRouterChainPrivate{parent}{

    };



public slots:

    void clearMidiRoutersFilters(){
        for (const QVariant &var : m_midiRoutersFilters) {

            if (var.canConvert<MidiRoutersFilter*>()) {
                delete var.value<MidiRoutersFilter*>();
            }
        }
        m_midiRoutersFilters.clear();

        emit midiRoutersFiltersChanged();
    }

    void addFilterMidiDestination(QString midiDestination){
        auto f = new FilterMidiDestination();
        f->setFilter(midiDestination);
        m_midiRoutersFilters.append(QVariant::fromValue(f));
    }
signals:


private:

};
