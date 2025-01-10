#include "MidiRouterChain.h"
#include "FilterMidiDestination.h"
#include "FilterNetworkDestination.h"
#include "../genPrpt/MidiRoutersFilter.h"
     MidiRouterChain::MidiRouterChain(QObject * parent) 
        : MidiRouterChainPrivate{parent}{

    };


    void MidiRouterChain::clearMidiRoutersFilters() 
    {
        for (const QVariant &var : m_midiRoutersFilters) {

            if (var.canConvert<MidiRoutersFilter*>()) {
                delete var.value<MidiRoutersFilter*>();
            }
        }
        m_midiRoutersFilters.clear();

        emit midiRoutersFiltersChanged();
    }

    void MidiRouterChain::addFilterMidiDestination(QString midiDestination) 
    {
        auto f = new FilterMidiDestination();
        f->setFilter(midiDestination);
        m_midiRoutersFilters.append(QVariant::fromValue(f));
        emit midiRoutersFiltersChanged();
    }

    void MidiRouterChain::addFilterToConsole(FilterToConsole::LogTo logTo, QString userData) 
    {
        auto f = new FilterToConsole();
        f->setFilter(logTo, userData);
        m_midiRoutersFilters.append(QVariant::fromValue(f));
        emit midiRoutersFiltersChanged();
    }

    void MidiRouterChain::addFilterNetworkDestination(QString serverName, int serverPort, QString baseMidiRouteInput) 
    {
        auto f = new FilterNetworkDestination();
        f->setFilter(serverName,  serverPort, baseMidiRouteInput);
        m_midiRoutersFilters.append(QVariant::fromValue(f));
        emit midiRoutersFiltersChanged();
    }

    void MidiRouterChain::addFilterFilterSchedule(FilterSchedule::DefferedType defferedType, int defferedTo ) 
    {
        auto f = new FilterSchedule();
        f->setFilter(defferedType, defferedTo);
        m_midiRoutersFilters.append(QVariant::fromValue(f));
        emit midiRoutersFiltersChanged();
    }

    void MidiRouterChain::addFilterAndTransform(QString name, FilterAndTransform::ConditionAction conditionAction, QString filterChannel, QString filterEvents, QString filterData1, QString filterData2 ) 
    {
        auto f = new FilterAndTransform();
        f->setFilter( name,  conditionAction,  filterChannel,
                    filterEvents,  filterData1,  filterData2 );
        m_midiRoutersFilters.append(QVariant::fromValue(f));
        emit midiRoutersFiltersChanged();
    }

    void MidiRouterChain::addEasyConfigMonitor() 
    {
        setIsEasyConfig(true);
        QJsonObject obj;
        obj["action"] = "monitor";
        QJsonDocument doc{obj};
        addFilterToConsole(FilterToConsole::LogTo::CLIENT,doc.toJson());
    }

    void MidiRouterChain::addEasyConfigPresetFilter(const MidiPresetControlEasyConfig &m) 
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

    void MidiRouterChain::addEasyConfigPresetLogOnOff(QString presetUuid, bool isMidiControlOn) 
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

    void MidiRouterChain::setEasyConfigChain(EasyConfig * easyConfig,EasyConfigRoute * easyConfigRoute) 
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

