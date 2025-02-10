#pragma once
#include "../genPrpt/FilterMidiDestinationPrivate.h"


class FilterMidiDestination : public FilterMidiDestinationPrivate

{
    Q_OBJECT

    QML_ELEMENT
public:
#line 22 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/FilterMidiDestination.hpp"
    explicit FilterMidiDestination(QObject *parent = nullptr);
public slots:
#line 32 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/FilterMidiDestination.hpp"
    void setFilter(QString input);
private:

};
