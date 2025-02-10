#line 7 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/FilterNetworkDestination.hpp"
#include "FilterNetworkDestination.h"
     FilterNetworkDestination::FilterNetworkDestination(QObject * parent) 
#line 24 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/FilterNetworkDestination.hpp"
    : FilterNetworkDestinationPrivate{parent}
    {
        setFilterType( FilterType::TO_NETWORK);
    };

    void FilterNetworkDestination::setFilter(QString serverName, int serverPort, QString baseMidiRouteInput) 
#line 34 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/FilterNetworkDestination.hpp"
    {
        setServerName(serverName);
        setServerPort(serverPort);
        setBaseMidiRouteInput(baseMidiRouteInput);
        setName(QString("To %1:%2 - %3").arg(serverName).arg(serverPort).arg(baseMidiRouteInput));
    }

