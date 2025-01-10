//-define-file body GenHpp/MidiRouterChain.cpp
//-define-file header GenHpp/MidiRouterChain.h
//-only-file header //-
#pragma once
//- #include "EasyConfig.h"
//- #include "FilterAndTransform.h"
//- #include "FilterSchedule.h"
//- #include "FilterToConsle.h"
//- #include "MidiPresetControlEasyConfig.h"
//- #include "../genPrpt/MidiRouterChainPrivate.h"
//-only-file body //-
//- #include "MidiRouterChain.h"
//- #include "FilterMidiDestination.h"
//- #include "FilterNetworkDestination.h"
//- #include "../genPrpt/MidiRoutersFilter.h"
//-only-file null
#include "EasyConfig.hpp"
#include "FilterAndTransform.hpp"
#include "FilterMidiDestination.hpp"
#include "FilterNetworkDestination.hpp"
#include "FilterSchedule.hpp"
#include "FilterToConsle.hpp"
#include "MidiPresetControlEasyConfig.hpp"
#include "../genPrpt/MidiRouterChainPrivate.hpp"
#include "../genPrpt/MidiRoutersFilter.hpp"
//-only-file header
#include <QtCore/qjsondocument.h>
#include <QtCore/qjsonobject.h>


//-var {PRE} "MidiRouterChain::"
class MidiRouterChain : public MidiRouterChainPrivate

{
    Q_OBJECT
    QML_ELEMENT
public:
    //- {function} 1 1
    explicit MidiRouterChain(QObject *parent = nullptr)
    //-only-file body
        : MidiRouterChainPrivate{parent}{

    };


    //-only-file header
public slots:
    //- {function} 0 1
    void clearMidiRoutersFilters()
    //-only-file body
    {
        for (const QVariant &var : m_midiRoutersFilters) {

            if (var.canConvert<MidiRoutersFilter*>()) {
                delete var.value<MidiRoutersFilter*>();
            }
        }
        m_midiRoutersFilters.clear();

        emit midiRoutersFiltersChanged();
    }

    //- {function} 0 1
    void delMidiRoutersFilter(const int id)
    //-only-file body
    {
        if (id < m_midiRoutersFilters.size())
        {
            auto var = m_midiRoutersFilters.at(id);
            if (var.canConvert<MidiRoutersFilter*>()) {
                delete var.value<MidiRoutersFilter*>();
            }

            m_midiRoutersFilters.removeAt(id);
            emit midiRoutersFiltersChanged();
        }
    }

    //- {function} 0 1
    void addFilterMidiDestination(QString midiDestination)
    //-only-file body
    {
        auto f = new FilterMidiDestination();
        f->setFilter(midiDestination);
        m_midiRoutersFilters.append(QVariant::fromValue(f));
        emit midiRoutersFiltersChanged();
    }

    //- {function} 0 1
    void addFilterToConsole(FilterToConsole::LogTo logTo, QString userData)
    //-only-file body
    {
        auto f = new FilterToConsole();
        f->setFilter(logTo, userData);
        m_midiRoutersFilters.append(QVariant::fromValue(f));
        emit midiRoutersFiltersChanged();
    }

    //- {function} 0 1
    void addFilterNetworkDestination(QString serverName, int serverPort, QString baseMidiRouteInput)
    //-only-file body
    {
        auto f = new FilterNetworkDestination();
        f->setFilter(serverName,  serverPort, baseMidiRouteInput);
        m_midiRoutersFilters.append(QVariant::fromValue(f));
        emit midiRoutersFiltersChanged();
    }

    //- {function} 0 1
    void addFilterFilterSchedule(FilterSchedule::DefferedType defferedType, int defferedTo )
    //-only-file body
    {
        auto f = new FilterSchedule();
        f->setFilter(defferedType, defferedTo);
        m_midiRoutersFilters.append(QVariant::fromValue(f));
        emit midiRoutersFiltersChanged();
    }

    //- {function} 0 1
    void addFilterAndTransform(QString name, FilterAndTransform::ConditionAction conditionAction, QString filterChannel,
                               QString filterEvents, QString filterData1, QString filterData2 )
    //-only-file body
    {
        auto f = new FilterAndTransform();
        f->setFilter( name,  conditionAction,  filterChannel,
                    filterEvents,  filterData1,  filterData2 );
        m_midiRoutersFilters.append(QVariant::fromValue(f));
        emit midiRoutersFiltersChanged();
    }

    //- {function} 0 1
    void addEasyConfigMonitor()
    //-only-file body
    {
        setIsEasyConfig(true);
        QJsonObject obj;
        obj["action"] = "monitor";
        QJsonDocument doc{obj};
        addFilterToConsole(FilterToConsole::LogTo::CLIENT,doc.toJson());
    }

    //- {function} 0 1
    void addEasyConfigPresetFilter(const MidiPresetControlEasyConfig &m)
    //-only-file body
    {

        setName("EasyConfig");
        setIsEasyConfig(true);
        EasyConfigRoute ecr{};
        ecr.setFromChannel(m.pmc->channel());
        ecr.setToChannel(m.pmc->channel());
        ecr.setFromSelectedMidiEventTypeId(m.pmc->eventTypeId());
        ecr.setToSelectedMidiEventTypeId(m.pmc->eventTypeId());
        ecr.setFromData1(m.pmc->data1());
        if (m.pmc->data2()!= -1){
            ecr.setFromCcOrNrpnStart(m.pmc->data2());
            ecr.setFromCcOrNrpnEnd(m.pmc->data2());
            ecr.setToCcOrNrpnStart(m.pmc->data2());
            ecr.setToCcOrNrpnEnd(m.pmc->data2());
        }
        auto easyConfigRouteFilter = ecr.getEasyConfigRouteFilter({});

        if (!easyConfigRouteFilter.isAllDefault) {
            addFilterAndTransform(
                "EasyConfig",
                FilterAndTransform::ConditionAction::
                DELETE_IF_NOT_MET_CONDITION,
                easyConfigRouteFilter.channelFilter,
                easyConfigRouteFilter.eventFilter,
                easyConfigRouteFilter.data1Filter,
                easyConfigRouteFilter.data2Filter
                );

        }
    }

    //- {function} 0 1
    void addEasyConfigPresetLogOnOff(QString presetUuid, bool isMidiControlOn)
    //-only-file body
    {
        setIsEasyConfig(true);
        setIsRunForPresetOnAndOff(true);
        QJsonObject obj;
        obj["action"] = "presetOnOff";
        obj["presetUuid"] = presetUuid;
        obj["isMidiControlOn"] = isMidiControlOn;
        QJsonDocument doc{obj};
        addFilterToConsole(FilterToConsole::LogTo::SERVER,doc.toJson());
    }

    //- {function} 0 1
    void setEasyConfigChain(EasyConfig *easyConfig,EasyConfigRoute *easyConfigRoute)
    //-only-file body
    {
        setName("EasyConfig");
        setIsEasyConfig(true);

        auto const toDestinationName = easyConfigRoute->toDestinationName();
        if (toDestinationName.isEmpty()) {
            return;
        }

        auto easyConfigRouteFilter = easyConfigRoute->getEasyConfigRouteFilter(easyConfig->keyboardSplits());

        if (!easyConfigRouteFilter.isAllDefault) {
            addFilterAndTransform(
                "EasyConfig",
                FilterAndTransform::ConditionAction::
                DELETE_IF_NOT_MET_CONDITION,
                easyConfigRouteFilter.channelFilter,
                easyConfigRouteFilter.eventFilter,
                easyConfigRouteFilter.data1Filter,
                easyConfigRouteFilter.data2Filter
                );

        }

        addFilterMidiDestination(toDestinationName);

    }

    //-only-file header
signals:


private:

};
