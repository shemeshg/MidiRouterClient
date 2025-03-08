//-define-file body GenHpp/MidiRouterChain.cpp
//-define-file header GenHpp/MidiRouterChain.h
//-only-file header //-
#pragma once

//-only-file body //-
//- #include "MidiRouterChain.h"

//- {include-header}
#include "EasyConfig.hpp" //- #include "EasyConfig.h"
//- {include-header}
#include "FilterAndTransform.hpp" //- #include "FilterAndTransform.h"
//- {include-header}
#include "FilterMidiDestination.hpp" //- #include "FilterMidiDestination.h"
//- {include-header}
#include "FilterNetworkDestination.hpp" //- #include "FilterNetworkDestination.h"
//- {include-header}
#include "FilterSchedule.hpp" //- #include "FilterSchedule.h"
//- {include-header}
#include "FilterToConsle.hpp" //- #include "FilterToConsle.h"
//- {include-header}
#include "MidiPresetControlEasyConfig.hpp" //- #include "MidiPresetControlEasyConfig.h"
//- {include-header}
#include "../genPrpt/MidiRouterChainPrivate.hpp" //- #include "../genPrpt/MidiRouterChainPrivate.h"
//-only-file null


//-only-file header
#include <QtCore/qjsondocument.h>
#include <QtCore/qjsonobject.h>

struct MidiPortInfo {
    QString serverName;
    QString serverPort;
    QString midiPort;
    bool isRemoteObject(){
        return !serverName.isEmpty() && !serverPort.isEmpty() && !midiPort.isEmpty();
    }
};

//-var {PRE} "MidiRouterChain::"
class MidiRouterChain : public MidiRouterChainPrivate

{
    Q_OBJECT
    QML_ELEMENT
public:
    //- {function} 1 1
    explicit MidiRouterChain(QObject *parent)
    //-only-file body
        : MidiRouterChainPrivate{parent}{
        setUuid(getUuId());
        setIsEasyConfig(false);
        setIsRunForPresetOnAndOff(false);
    };

    //- {function} 1 1
    virtual ~MidiRouterChain()
    //-only-file body
    {
        clearMidiRoutersFilters();
    }

    //- {fn}
    QJsonObject genJson()
    //-only-file body
    {
        QJsonObject midiRouterChainObj;
        midiRouterChainObj["uuid"] = uuid();
        midiRouterChainObj["name"] = name();
        midiRouterChainObj["isEasyConfig"] = isEasyConfig();
        midiRouterChainObj["isRunForPresetOnAndOff"] = isRunForPresetOnAndOff();
        midiRouterChainObj["midiRoutersFilters"] = getJsonMidiRoutersFilters();
        return midiRouterChainObj;
    }

    //-only-file header
public slots:
    //- {fn}
    void clearMidiRoutersFilters()
    //-only-file body
    {
        for (const QVariant &var : m_midiRoutersFilters) {

            deleteVarIfCanConvert(var);
        }
        m_midiRoutersFilters.clear();

        emit midiRoutersFiltersChanged();
    }

    //- {fn}
    void delMidiRoutersFilter(const int id)
    //-only-file body
    {
        if (id < m_midiRoutersFilters.size())
        {
            auto var = m_midiRoutersFilters.at(id);
            deleteVarIfCanConvert(var);

            m_midiRoutersFilters.removeAt(id);
            emit midiRoutersFiltersChanged();
        }
    }

    //- {fn}
    FilterMidiDestination* addFilterMidiDestination(QString midiDestination)
    //-only-file body
    {
        auto f = new FilterMidiDestination(this);
        f->setFilter(midiDestination);
        m_midiRoutersFilters.append(QVariant::fromValue(f));
        emit midiRoutersFiltersChanged();
        return f;
    }

    //- {fn}
    FilterToConsole* addFilterToConsole(FilterToConsole::LogTo logTo, QString userData)
    //-only-file body
    {
        auto f = new FilterToConsole(this);
        f->setFilter(logTo, userData);
        m_midiRoutersFilters.append(QVariant::fromValue(f));
        emit midiRoutersFiltersChanged();
        return f;
    }

    //- {fn}
    FilterNetworkDestination* addFilterNetworkDestination(QString serverName, int serverPort, QString baseMidiRouteInput)
    //-only-file body
    {
        auto f = new FilterNetworkDestination(this);
        f->setFilter(serverName,  serverPort, baseMidiRouteInput);
        m_midiRoutersFilters.append(QVariant::fromValue(f));
        emit midiRoutersFiltersChanged();
        return f;
    }

    //- {fn}
    FilterSchedule* addFilterFilterSchedule(FilterSchedule::DefferedType defferedType, int defferedTo )
    //-only-file body
    {
        auto f = new FilterSchedule(this);
        f->setFilter(defferedType, defferedTo);
        m_midiRoutersFilters.append(QVariant::fromValue(f));
        emit midiRoutersFiltersChanged();
        return f;
    }

    //- {fn}
    FilterAndTransform* addFilterAndTransform(QString name, FilterAndTransform::ConditionAction conditionAction, QString filterChannel,
                               QString filterEvents, QString filterData1, QString filterData2 )
    //-only-file body
    {
        auto f = new FilterAndTransform(this);
        f->setFilter( name,  conditionAction,  filterChannel,
                    filterEvents,  filterData1,  filterData2 );
        m_midiRoutersFilters.append(QVariant::fromValue(f));
        emit midiRoutersFiltersChanged();
        return f;
    }

    //- {fn}
    void addEasyConfigMonitor()
    //-only-file body
    {
        setIsEasyConfig(true);
        setName("EasyConfig Monitor");
        QJsonObject obj;
        obj["action"] = "monitor";
        QJsonDocument doc{obj};
        addFilterToConsole(FilterToConsole::LogTo::CLIENT,doc.toJson());
    }

    //- {fn}
    void addEasyConfigPresetFilter(const MidiPresetControlEasyConfig &m)
    //-only-file body
    {

        setName("EasyConfig");
        setIsEasyConfig(true);
        EasyConfigRoute ecr{this};
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

    //- {fn}
    void addEasyConfigPresetLogOnOff(bool isMidiControlOn, const QString &presetUuid)
    //-only-file body
    {
        setIsEasyConfig(true);
        setIsRunForPresetOnAndOff(true);
        QJsonObject obj;
        obj["action"] = "presetOnOff";
        obj["isMidiControlOn"] = isMidiControlOn;
        obj["presetUuid"] = presetUuid;
        QJsonDocument doc{obj};
        addFilterToConsole(FilterToConsole::LogTo::SERVER,doc.toJson());
    }

    //- {fn}
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
        auto s = parseMidiPortName(toDestinationName);

        if (s.isRemoteObject()) {
            addFilterNetworkDestination(s.serverName,s.serverPort.toInt(),s.midiPort);
        } else {
            addFilterMidiDestination(toDestinationName);

        }

    }

    //-only-file header
signals:


private:


    //- {fn}
    MidiPortInfo parseMidiPortName(const QString& completeMidiPortName)
    //-only-file body
    {
        QRegularExpression regex(R"(^([a-zA-Z0-9._-]+):(\d+)(\/([\ a-zA-Z0-9._-]+)?)?$)");
        QRegularExpressionMatch match = regex.match(completeMidiPortName);

        MidiPortInfo midiPortInfo;

        if (match.hasMatch()) {
            midiPortInfo.serverName = match.captured(1);
            midiPortInfo.serverPort = match.captured(2);
            midiPortInfo.midiPort = match.captured(4);
        }

        return midiPortInfo;
    }

    //- {fn}
    void deleteVarIfCanConvert(const QVariant &var)
    //-only-file body
    {
        if (var.canConvert<FilterMidiDestination*>()) {
            delete var.value<FilterMidiDestination*>();
        } else if (var.canConvert<FilterToConsole*>()) {
            delete var.value<FilterToConsole*>();
        } else if (var.canConvert<FilterNetworkDestination*>()) {
            delete var.value<FilterNetworkDestination*>();
        } else if (var.canConvert<FilterSchedule*>()) {
            delete var.value<FilterSchedule*>();
        } else if (var.canConvert<FilterAndTransform*>()) {
            delete var.value<FilterAndTransform*>();
        }
    }

    //- {fn}
    QJsonArray getJsonMidiRoutersFilters()
    //-only-file body
    {
        QJsonArray ary;
        for (int i=0;i<midiRoutersFilters().length();i++){
            auto midiRoutersFilter = midiRoutersFilters().at(i);
            QJsonObject filterObj;

            if (midiRoutersFilter.canConvert<MidiRoutersFilter*>()) {
                auto filter = midiRoutersFilter.value<MidiRoutersFilter*>();
                ary.append(filter->genJson());
            }
        }
        return ary;
    }

    //-only-file header
};
