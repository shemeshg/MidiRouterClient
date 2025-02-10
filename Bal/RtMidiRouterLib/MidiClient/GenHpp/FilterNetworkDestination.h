#pragma once
#include "../genPrpt/FilterNetworkDestinationPrivate.h"


class FilterNetworkDestination : public FilterNetworkDestinationPrivate

{
    Q_OBJECT

    QML_ELEMENT
public:
#line 22 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/FilterNetworkDestination.hpp"
    explicit FilterNetworkDestination(QObject *parent = nullptr);
public slots:
#line 32 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/FilterNetworkDestination.hpp"
    void setFilter(QString serverName, int serverPort, QString baseMidiRouteInput);
private:

};
