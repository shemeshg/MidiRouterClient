#pragma once
#include "../genPrpt/FilterSchedulePrivate.h"

class FilterSchedule : public FilterSchedulePrivate

{
    Q_OBJECT

    QML_ELEMENT
public:
#line 21 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/FilterSchedule.hpp"
    explicit FilterSchedule(QObject *parent = nullptr);
public slots:
#line 31 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/FilterSchedule.hpp"
    void setFilter(DefferedType defferedType, int defferedTo );
private:

};
