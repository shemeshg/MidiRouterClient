#pragma once
#include "EasyConfig.h"
#include "FilterAndTransform.h"
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

    void addFilterAndTransform(QString name, FilterAndTransform::ConditionAction conditionAction, QString filterChannel,
                               QString filterEvents, QString filterData1, QString filterData2 ){
        auto f = new FilterAndTransform();
        f->setFilter( name,  conditionAction,  filterChannel,
                    filterEvents,  filterData1,  filterData2 );
        m_midiRoutersFilters.append(QVariant::fromValue(f));
    }

    void setEasyConfigChain(EasyConfig *easyConfig,EasyConfigRoute *easyConfigRoute){
        setName("EasyConfig");
        setIsEasyConfig(true);

        auto const toDestinationName = easyConfigRoute->toDestinationName();
        if (toDestinationName.isEmpty()) {
            return;
        }
        bool isAllDefault = true;
        QString channelFilter = "[[0, 16, 0]]";
        if (easyConfigRoute->fromChannel() != -1) {
            isAllDefault = false;
            channelFilter = QString{"[[%0, %1]]"}
                                .arg(easyConfigRoute->fromChannel())
                                .arg(easyConfigRoute->toChannel());
        }
        QString eventFilter = "[[0, 16, 0]]";
        if (easyConfigRoute->fromSelectedMidiEventTypeId() != 0) {
            isAllDefault = false;
            if (easyConfigRoute->fromSelectedMidiEventTypeId() ==
                    easyConfigRoute->toSelectedMidiEventTypeId() &&
                easyConfigRoute->toSelectedMidiEventTypeId() ==
                    (int)EasyConfig::DropdownMidiEventTypeEnum::noteOnOf) {
                eventFilter = QString{"[[%0], [%1]]"}
                                  .arg((int)EasyConfig::EventTypes::noteoff)
                                  .arg((int)EasyConfig::EventTypes::noteon);
            } else {
                eventFilter =
                    QString{"[[%0], [%1]]"}
                        .arg((int)easyConfig->dropdownMidiEventTypeEnum
                                 [(EasyConfig::DropdownMidiEventTypeEnum)
                                  easyConfigRoute->fromSelectedMidiEventTypeId()])
                        .arg((int)easyConfig->dropdownMidiEventTypeEnum
                                 [(EasyConfig::DropdownMidiEventTypeEnum)
                                  easyConfigRoute->toSelectedMidiEventTypeId()]);
            }
        }

        QString data1Filter = "[[0, 127, 0]]";
        QString data2Filter = "[[0, 127, 0]]";
        int splitRangeId = easyConfigRoute->splitRangeId();
        if (splitRangeId != -1) {

            QList<int> keyboardSplits = easyConfig->keyboardSplits();
            if (!keyboardSplits.contains(8)) {
                keyboardSplits.append(8);
                splitRangeId++;
            }
            if (!keyboardSplits.contains(98)) {
                keyboardSplits.append(98);
                splitRangeId++;
            }
            sortUniq(keyboardSplits);
            int fromKey = keyboardSplits.at(splitRangeId);
            int toKey = keyboardSplits.at(splitRangeId + 1);
            data1Filter = QString{"[[%0, %1, %2]]"}.arg(
                fromKey, toKey, fromKey + easyConfigRoute->transpose());
        } else {
            data1Filter =
                QString{"[[0, 127, %0]]"}.arg(0 + easyConfigRoute->transpose());
        }

        if (easyConfigRoute->fromData1() != -1) {
            if (easyConfigRoute->toData1() == -1) {
                data1Filter = QString{"[[%0]]"}.arg(easyConfigRoute->fromData1());
            } else {
                data1Filter = QString{"[[%0, %1]]"}
                                  .arg(easyConfigRoute->fromData1())
                                  .arg(easyConfigRoute->toData1());
            }
        }
        if (easyConfigRoute->fromData1() != -1 &&
            easyConfigRoute->toData1() != -1) {
            data1Filter = QString{"[[%0 %1]]"}
                              .arg(easyConfigRoute->fromData1())
                              .arg(easyConfigRoute->toData1());
        }
        if (easyConfigRoute->fromData1() != -1 ||
            easyConfigRoute->toData1() != -1) {
            data2Filter = QString{"[[%0, %1, %2, %3]]"}
                              .arg(easyConfigRoute->fromCcOrNrpnStart())
                              .arg(easyConfigRoute->fromCcOrNrpnEnd())
                              .arg(easyConfigRoute->toCcOrNrpnStart())
                              .arg(easyConfigRoute->toCcOrNrpnEnd());
        }

        if (!isAllDefault) {
            addFilterAndTransform(
                "EasyConfig",
                FilterAndTransform::ConditionAction::
                DELETE_IF_NOT_MET_CONDITION,
                channelFilter, eventFilter, data1Filter, data2Filter
                );
            qDebug()<<"***EASY CONFIG FILTER "<<channelFilter<<eventFilter<<data1Filter<<data2Filter;
        }

        addFilterMidiDestination(toDestinationName);

    }

signals:


private:
    void sortUniq(QList<int> &list) {
        QSet<int> set(list.begin(), list.end());
        list = QList<int>(set.begin(), set.end());
        std::sort(list.begin(), list.end()); // Sort the list
    }
};
