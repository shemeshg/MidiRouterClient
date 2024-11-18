#pragma once
#include "FilterMidiDestination.h"
#include "FilterNetworkDestination.h"
#include "FilterSchedule.h"
#include "FilterToConsle.h"
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

    void addFilterToConsole(FilterToConsole::LogTo logTo, QString userData){
        auto f = new FilterToConsole();
        f->setFilter(logTo, userData);
        m_midiRoutersFilters.append(QVariant::fromValue(f));
    }

    void addFilterNetworkDestination(QString serverName, int serverPort, QString baseMidiRouteInput){
        auto f = new FilterNetworkDestination();
        f->setFilter(serverName,  serverPort, baseMidiRouteInput);
        m_midiRoutersFilters.append(QVariant::fromValue(f));
    }

    void addFilterFilterSchedule(FilterSchedule::DefferedType defferedType, int defferedTo ){
        auto f = new FilterSchedule();
        f->setFilter(defferedType, defferedTo);
        m_midiRoutersFilters.append(QVariant::fromValue(f));
    }
signals:


private:

};
