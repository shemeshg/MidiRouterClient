#pragma once
#include "../genPrpt/EasyConfigRoutePrivate.h"




struct EasyConfigRouteFilter{
    QString channelFilter, eventFilter, data1Filter, data2Filter;
    bool isAllDefault;
};

class EasyConfigRoute : public EasyConfigRoutePrivate

{
    Q_OBJECT
    QML_ELEMENT
public:
#line 28 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/EasyConfigRoute.hpp"
    explicit EasyConfigRoute(QObject *parent = nullptr);
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

#line 91 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/EasyConfigRoute.hpp"
    EasyConfigRouteFilter getEasyConfigRouteFilter(const QList<int> &keyboardSplits);
public slots:

private:
#line 191 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/EasyConfigRoute.hpp"
    void sortUniq(QList<int> &list);
};
