//-define-file body GenHpp/FilterNetworkDestination.cpp
//-define-file header GenHpp/FilterNetworkDestination.h
//-only-file header //-
#pragma once
//- #include "../genPrpt/FilterNetworkDestinationPrivate.h"
//-only-file body //-
//- #include "FilterNetworkDestination.h"
//- #include "MidiClientUtil.h"
//-only-file null
#include "MidiClientUtil.hpp"
#include "../genPrpt/FilterNetworkDestinationPrivate.hpp"
//-only-file header


//-var {PRE} "FilterNetworkDestination::"
class FilterNetworkDestination : public FilterNetworkDestinationPrivate

{
    Q_OBJECT

    QML_ELEMENT
public:
    //- {function} 1 1
    explicit FilterNetworkDestination(QObject *parent = nullptr)
    //-only-file body
    : FilterNetworkDestinationPrivate{parent}
    {
        setFilterType( FilterType::TO_NETWORK);
        setUuid(getUuId());
    };

    //-only-file header
public slots:
    //- {fn}
    void setFilter(QString serverName, int serverPort, QString baseMidiRouteInput)
    //-only-file body
    {
        setServerName(serverName);
        setServerPort(serverPort);
        setBaseMidiRouteInput(baseMidiRouteInput);
        setName(QString("To %1:%2 - %3").arg(serverName).arg(serverPort).arg(baseMidiRouteInput));
    }

    //-only-file header
private:

};
