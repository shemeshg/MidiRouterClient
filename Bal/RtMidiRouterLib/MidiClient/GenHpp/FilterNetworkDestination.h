#pragma once
#include "../genPrpt/FilterNetworkDestinationPrivate.h"

class FilterNetworkDestination : public FilterNetworkDestinationPrivate

{
    Q_OBJECT

    QML_ELEMENT
public:
    explicit FilterNetworkDestination(QObject *parent = nullptr);
public slots:
    void setFilter(QString serverName, int serverPort, QString baseMidiRouteInput);
private:

};
