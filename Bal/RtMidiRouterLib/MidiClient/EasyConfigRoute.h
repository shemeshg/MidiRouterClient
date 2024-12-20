

#pragma once
#include "EasyConfigRoutePrivate.h"


struct EasyConfigRouteFilter{
    QString channelFilter, eventFilter, data1Filter, data2Filter;
    bool isAllDefault;
};

class EasyConfigRoute : public EasyConfigRoutePrivate

{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit EasyConfigRoute(QObject *parent = nullptr)
        : EasyConfigRoutePrivate{parent} {};


    enum class DropdownMidiEventTypeEnum {
        allEvents = 0,
        noteOnOf = 1,
        noteoff = 2,
        noteon = 3,
        keyaftertouch = 4,
        controlchange = 5,
        channelmode = 6,
        nrpn = 7,
        programchange = 8,
        channelaftertouch = 9,
        pitchbend = 10
    };

    enum class EventTypes {
        noteoff = 8,
        noteon = 9,
        keyaftertouch = 10,
        controlchange = 11,
        channelmode = 11,
        nrpn = 100,
        programchange = 12,
        channelaftertouch = 13,
        pitchbend = 14
    };

    QMap<DropdownMidiEventTypeEnum, EventTypes> dropdownMidiEventTypeEnum = {
        {DropdownMidiEventTypeEnum::noteoff, EventTypes::noteoff},
        {DropdownMidiEventTypeEnum::noteon, EventTypes::noteon},
        {DropdownMidiEventTypeEnum::keyaftertouch, EventTypes::keyaftertouch},
        {DropdownMidiEventTypeEnum::controlchange, EventTypes::controlchange},
        {DropdownMidiEventTypeEnum::channelmode, EventTypes::channelmode},
        {DropdownMidiEventTypeEnum::nrpn, EventTypes::nrpn},
        {DropdownMidiEventTypeEnum::programchange, EventTypes::programchange},
        {DropdownMidiEventTypeEnum::channelaftertouch, EventTypes::channelaftertouch},
        {DropdownMidiEventTypeEnum::pitchbend, EventTypes::pitchbend}
    };

    EasyConfigRouteFilter getEasyConfigRouteFilter(const QList<int> &keyboardSplits){
        EasyConfigRouteFilter ecf;



        bool isAllDefault = true;
        QString channelFilter = "[[0, 16, 0]]";
        if (fromChannel() != -1) {
            isAllDefault = false;
            channelFilter = QString{"[[%0, %1]]"}
                                .arg(fromChannel())
                                .arg(toChannel());
        }
        QString eventFilter = "[[0, 16, 0]]";
        if (fromSelectedMidiEventTypeId() != 0) {
            isAllDefault = false;
            if (fromSelectedMidiEventTypeId() ==
                    toSelectedMidiEventTypeId() &&
                toSelectedMidiEventTypeId() ==
                    (int)DropdownMidiEventTypeEnum::noteOnOf) {
                eventFilter = QString{"[[%0], [%1]]"}
                                  .arg((int)EventTypes::noteoff)
                                  .arg((int)EventTypes::noteon);
            } else {
                eventFilter =
                    QString{"[[%0], [%1]]"}
                        .arg((int)dropdownMidiEventTypeEnum
                                 [(DropdownMidiEventTypeEnum)
                                  fromSelectedMidiEventTypeId()])
                        .arg((int)dropdownMidiEventTypeEnum
                                 [(DropdownMidiEventTypeEnum)
                                  toSelectedMidiEventTypeId()]);
            }
        }

        QString data1Filter = "[[0, 127, 0]]";
        QString data2Filter = "[[0, 127, 0]]";
        int vSplitRangeId = splitRangeId();
        if (vSplitRangeId != -1) {

            QList<int> vKeyboardSplits = keyboardSplits;
            if (!vKeyboardSplits.contains(8)) {
                vKeyboardSplits.append(8);
                vSplitRangeId++;
            }
            if (!vKeyboardSplits.contains(98)) {
                vKeyboardSplits.append(98);
                vSplitRangeId++;
            }
            sortUniq(vKeyboardSplits);
            int fromKey = vKeyboardSplits.at(vSplitRangeId);
            int toKey = vKeyboardSplits.at(vSplitRangeId + 1);
            data1Filter = QString{"[[%0, %1, %2]]"}.arg(
                fromKey, toKey, fromKey + transpose());
        } else {
            data1Filter =
                QString{"[[0, 127, %0]]"}.arg(0 + transpose());
        }

        if (fromData1() != -1) {
            if (toData1() == -1) {
                data1Filter = QString{"[[%0]]"}.arg(fromData1());
            } else {
                data1Filter = QString{"[[%0, %1]]"}
                                  .arg(fromData1())
                                  .arg(toData1());
            }
        }
        if (fromData1() != -1 &&
            toData1() != -1) {
            data1Filter = QString{"[[%0 %1]]"}
                              .arg(fromData1())
                              .arg(toData1());
        }
        if (fromData1() != -1 ||
            toData1() != -1) {
            data2Filter = QString{"[[%0, %1, %2, %3]]"}
                              .arg(fromCcOrNrpnStart())
                              .arg(fromCcOrNrpnEnd())
                              .arg(toCcOrNrpnStart())
                              .arg(toCcOrNrpnEnd());
        }

        ecf.isAllDefault = isAllDefault;
        ecf.channelFilter = channelFilter;
        ecf.eventFilter = eventFilter;
        ecf.data1Filter = data1Filter;
        ecf.data2Filter = data2Filter;


        return ecf;
    }
public slots:

private:
    void sortUniq(QList<int> &list) {
        QSet<int> set(list.begin(), list.end());
        list = QList<int>(set.begin(), set.end());
        std::sort(list.begin(), list.end()); // Sort the list
    }
};
