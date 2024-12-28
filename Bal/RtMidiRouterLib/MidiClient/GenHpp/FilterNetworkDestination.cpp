#include "FilterNetworkDestination.h"
     FilterNetworkDestination::FilterNetworkDestination(QObject * parent) 
    : FilterNetworkDestinationPrivate{parent}
    {
        setFilterType( FilterType::TO_NETWORK);
    };

    void FilterNetworkDestination::setFilter(QString serverName, int serverPort, QString baseMidiRouteInput) 
    {
        setServerName(serverName);
        setServerPort(serverPort);
        setBaseMidiRouteInput(baseMidiRouteInput);
        setName(QString("To %1:%2 - %3").arg(serverName).arg(serverPort).arg(baseMidiRouteInput));
    }

