#line 7 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/FilterAndTransform.hpp"
#include "FilterAndTransform.h"
     FilterAndTransform::FilterAndTransform(QObject * parent) 
#line 24 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/FilterAndTransform.hpp"
    : FilterAndTransformPrivate{parent}
    {
         setFilterType( FilterType::FILTER_AND_TRANSFORM);
    };

    void FilterAndTransform::setFilter(QString name, ConditionAction conditionAction, QString filterChannel, QString filterEvents, QString filterData1, QString filterData2) 
#line 35 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/FilterAndTransform.hpp"
    {
        setName(name);
        setConditionAction(conditionAction);
        setFilterChannel(filterChannel);
        setFilterEvents(filterEvents);
        setFilterData1(filterData1);
        setFilterData2(filterData2);
    }

