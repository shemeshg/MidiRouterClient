#include "EasyConfigRoute.h"
     EasyConfigRoute::EasyConfigRoute(QObject * parent) 
        : EasyConfigRoutePrivate{parent}{
        setSplitRangeId(-1);
        setFromSelectedMidiEventTypeId(0);
        setFromChannel(-1);
        setFromData1(-1);
        setTranspose(0);

        setFromCcOrNrpnStart(0);
        setFromCcOrNrpnEnd(127);
        setToCcOrNrpnStart(0);
        setToCcOrNrpnEnd(127);

        setToSelectedMidiEventTypeId(0);
        setToChannel(-1);
        setToData1(-1);

        setToDestinationName("");

    };


    EasyConfigRouteFilter EasyConfigRoute::getEasyConfigRouteFilter(const QList<int> &keyboardSplits) 
    {
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

    void EasyConfigRoute::sortUniq(QList<int> &list) 
    {
        QSet<int> set(list.begin(), list.end());
        list = QList<int>(set.begin(), set.end());
        std::sort(list.begin(), list.end()); // Sort the list
    }
