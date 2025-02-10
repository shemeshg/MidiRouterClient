#line 12 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/MidiRouterChain.hpp"
#include "MidiRouterChain.h"
#include "FilterMidiDestination.h"
#include "FilterNetworkDestination.h"
#include "../genPrpt/MidiRoutersFilter.h"
     MidiRouterChain::MidiRouterChain(QObject * parent) 
#line 41 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/MidiRouterChain.hpp"
        : MidiRouterChainPrivate{parent}{

    };


    void MidiRouterChain::clearMidiRoutersFilters() 
#line 51 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/MidiRouterChain.hpp"
    {
        for (const QVariant &var : m_midiRoutersFilters) {

            if (var.canConvert<MidiRoutersFilter*>()) {
                delete var.value<MidiRoutersFilter*>();
            }
        }
        m_midiRoutersFilters.clear();

        emit midiRoutersFiltersChanged();
    }

    void MidiRouterChain::delMidiRoutersFilter(const int id) 
#line 66 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/MidiRouterChain.hpp"
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

    void MidiRouterChain::addFilterMidiDestination(QString midiDestination) 
#line 82 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/MidiRouterChain.hpp"
    {
        auto f = new FilterMidiDestination();
        f->setFilter(midiDestination);
        m_midiRoutersFilters.append(QVariant::fromValue(f));
        emit midiRoutersFiltersChanged();
    }

    void MidiRouterChain::addFilterToConsole(FilterToConsole::LogTo logTo, QString userData) 
#line 92 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/MidiRouterChain.hpp"
    {
        auto f = new FilterToConsole();
        f->setFilter(logTo, userData);
        m_midiRoutersFilters.append(QVariant::fromValue(f));
        emit midiRoutersFiltersChanged();
    }

    void MidiRouterChain::addFilterNetworkDestination(QString serverName, int serverPort, QString baseMidiRouteInput) 
#line 102 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/MidiRouterChain.hpp"
    {
        auto f = new FilterNetworkDestination();
        f->setFilter(serverName,  serverPort, baseMidiRouteInput);
        m_midiRoutersFilters.append(QVariant::fromValue(f));
        emit midiRoutersFiltersChanged();
    }

    void MidiRouterChain::addFilterFilterSchedule(FilterSchedule::DefferedType defferedType, int defferedTo ) 
#line 112 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/MidiRouterChain.hpp"
    {
        auto f = new FilterSchedule();
        f->setFilter(defferedType, defferedTo);
        m_midiRoutersFilters.append(QVariant::fromValue(f));
        emit midiRoutersFiltersChanged();
    }

    void MidiRouterChain::addFilterAndTransform(QString name, FilterAndTransform::ConditionAction conditionAction, QString filterChannel, QString filterEvents, QString filterData1, QString filterData2 ) 
#line 123 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/MidiRouterChain.hpp"
    {
        auto f = new FilterAndTransform();
        f->setFilter( name,  conditionAction,  filterChannel,
                    filterEvents,  filterData1,  filterData2 );
        m_midiRoutersFilters.append(QVariant::fromValue(f));
        emit midiRoutersFiltersChanged();
    }

    void MidiRouterChain::addEasyConfigMonitor() 
#line 134 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/MidiRouterChain.hpp"
    {
        setIsEasyConfig(true);
        QJsonObject obj;
        obj["action"] = "monitor";
        QJsonDocument doc{obj};
        addFilterToConsole(FilterToConsole::LogTo::CLIENT,doc.toJson());
    }

    void MidiRouterChain::addEasyConfigPresetFilter(const MidiPresetControlEasyConfig &m) 
#line 145 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/MidiRouterChain.hpp"
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
#line 180 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/MidiRouterChain.hpp"
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
#line 194 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/MidiRouterChain.hpp"
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

