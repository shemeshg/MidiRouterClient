

#pragma once
#include "EasyConfigPrivate.h"
#include "EasyConfigRoute.h"

class EasyConfig : public EasyConfigPrivate

{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit EasyConfig(QObject *parent = nullptr)
        : EasyConfigPrivate{parent} {};

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

    void clearEasyConfigRoute(){
        for (const EasyConfigRoute *item : m_easyConfigRoutes) {
            delete item;
        }
        // Clear the outer list
        m_easyConfigRoutes.clear();
        emit easyConfigRoutesChanged();
    }

    void addEasyConfigRoute(EasyConfigRoute *itm){
        m_easyConfigRoutes.push_back(itm);
        emit easyConfigRoutesChanged();
    }



public slots:

private:
};
