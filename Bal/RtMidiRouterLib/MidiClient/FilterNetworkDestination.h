#pragma once

#include "FilterNetworkDestinationPrivate.h"

class FilterNetworkDestination : public FilterNetworkDestinationPrivate

{
    Q_OBJECT

    QML_ELEMENT
public:
    explicit FilterNetworkDestination(QObject *parent = nullptr){

    };

public slots:
    void setFilter(QString serverName, int serverPort, QString baseMidiRouteInput){
        setServerName(serverName);
        setServerPort(serverPort);
        setBaseMidiRouteInput(baseMidiRouteInput);
        setName(QString("To %1:%2 - %3").arg(serverName).arg(serverPort).arg(baseMidiRouteInput));
    }

private:

};
