//-define-file body GenHpp/EasyConfigRoute.cpp
//-define-file header GenHpp/EasyConfigRoute.h
//-only-file header //-
#pragma once
//-only-file body //-
//- #include "EasyConfigRoute.h"

//- {include-header}
#include "../genPrpt/EasyConfigRoutePrivate.hpp" //- #include "../genPrpt/EasyConfigRoutePrivate.h"
//- {include-header}
#include "MidiClientUtil.hpp" //- #include "MidiClientUtil.h"

//-only-file header
struct EasyConfigRouteFilter{
    QString channelFilter, eventFilter, data1Filter, data2Filter;
    bool isAllDefault;
};

//-var {PRE} "EasyConfigRoute::"
class EasyConfigRoute : public EasyConfigRoutePrivate

{
    Q_OBJECT
    QML_ELEMENT
public:
    //- {function} 1 1
    explicit EasyConfigRoute(QObject *parent)
        //-only-file body
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
        setUuid(getUuId());

    };


    //-only-file header
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

    //- {fn}
    QJsonObject genJson()
    //-only-file body
    {
        QJsonObject obj;
        obj["uuid"] = uuid();
        obj["splitRangeId"] = splitRangeId();
        obj["fromSelectedMidiEventTypeId"] = fromSelectedMidiEventTypeId();
        obj["fromChannel"] = fromChannel();
        obj["fromData1"] = fromData1();
        obj["transpose"] = transpose();
        obj["fromCcOrNrpnStart"] = fromCcOrNrpnStart();
        obj["fromCcOrNrpnEnd"] = fromCcOrNrpnEnd();
        obj["toCcOrNrpnStart"] = toCcOrNrpnStart();
        obj["toCcOrNrpnEnd"] = toCcOrNrpnEnd();
        obj["toSelectedMidiEventTypeId"] = toSelectedMidiEventTypeId();
        obj["toChannel"] = toChannel();
        obj["toData1"] = toData1();
        obj["toDestinationName"] = toDestinationName();
        return obj;
    }

    //- {fn}
    EasyConfigRouteFilter getEasyConfigRouteFilter(const QList<int> &keyboardSplits)
    //-only-file body
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
            }
            else if (fromSelectedMidiEventTypeId() ==   (int)DropdownMidiEventTypeEnum::noteOnOf){
                eventFilter = QString{"[[%0,%2], [%1,%2]]"}
                                  .arg((int)EventTypes::noteoff)
                                  .arg((int)EventTypes::noteon)
                                  .arg((int)dropdownMidiEventTypeEnum
                                           [(DropdownMidiEventTypeEnum)
                                            toSelectedMidiEventTypeId()]);
            }
            else {
                eventFilter =
                    QString{"[[%0, %1]]"}
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
        if (vSplitRangeId != -1 &&
            (
                fromSelectedMidiEventTypeId() == (int)DropdownMidiEventTypeEnum::noteOnOf ||
                fromSelectedMidiEventTypeId() == (int)DropdownMidiEventTypeEnum::noteon ||
                fromSelectedMidiEventTypeId() == (int)DropdownMidiEventTypeEnum::noteoff
                )) {

            QList<int> vKeyboardSplits = keyboardSplits;
            if (!vKeyboardSplits.contains(8)) {
                vKeyboardSplits.append(8);                
            }
            if (!vKeyboardSplits.contains(98)) {
                vKeyboardSplits.append(98);                
            }
            sortUniq(vKeyboardSplits);
            int fromKey = vKeyboardSplits.at(vSplitRangeId);
            int toKey = vKeyboardSplits.at(vSplitRangeId + 1);

            data1Filter = QString{"[[%0, %1, %2]]"}.arg(fromKey).arg(toKey).arg(fromKey + transpose());
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

        if (fromCcOrNrpnStart()!= -1 &&
            toCcOrNrpnStart() != -1){

            if (fromCcOrNrpnStart() == fromCcOrNrpnEnd() &&
                toCcOrNrpnStart() == toCcOrNrpnEnd() && fromCcOrNrpnStart() == toCcOrNrpnStart()) {
                data2Filter = QString{"[[%0 %1]]"}
                                  .arg(fromData1())
                                  .arg(toData1());
            } else {
                data2Filter = QString{"[[%0, %1, %2, %3]]"}
                                  .arg(fromCcOrNrpnStart())
                                  .arg(fromCcOrNrpnEnd())
                                  .arg(toCcOrNrpnStart())
                                  .arg(toCcOrNrpnEnd());
            }
        }


        ecf.isAllDefault = isAllDefault;
        ecf.channelFilter = channelFilter;
        ecf.eventFilter = eventFilter;
        ecf.data1Filter = data1Filter;
        ecf.data2Filter = data2Filter;


        return ecf;
    }

    //-only-file header
public slots:

private:
    //- {fn}
    void sortUniq(QList<int> &list)
    //-only-file body
    {
        QSet<int> set(list.begin(), list.end());
        list = QList<int>(set.begin(), set.end());
        std::sort(list.begin(), list.end()); // Sort the list
    }
    //-only-file header
};
