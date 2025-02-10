#line 7 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/FilterSchedule.hpp"
#include "FilterSchedule.h"
     FilterSchedule::FilterSchedule(QObject * parent) 
#line 23 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/FilterSchedule.hpp"
    : FilterSchedulePrivate{parent}
    {
        setFilterType( FilterType::SCHEDULE_TO);
    };

    void FilterSchedule::setFilter(DefferedType defferedType, int defferedTo ) 
#line 33 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/FilterSchedule.hpp"
    {
        setDefferedType(defferedType);
        setDefferedTo(defferedTo);

        QMap<DefferedType, QString> defferedTypeToString = {
            {DefferedType::IN_SPP, "IN_SPP"},
            {DefferedType::IN_BAR, "IN_BAR"},
            {DefferedType::AT_SPP, "AT_SPP"},
            {DefferedType::AT_BAR, "AT_BAR"},
            {DefferedType::QUANTIZE_SPP, "QUANTIZE_SPP"},
            {DefferedType::QUANTIZE_BAR, "QUANTIZE_BAR"}
        };

        setName(
            QString("Schedule %1 %2").arg(defferedTypeToString.value(defferedType)).arg(defferedTo)
            );
    }

