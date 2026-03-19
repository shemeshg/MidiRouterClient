//-define-file body GenHpp/FilterNetworkDestination.cpp
//-define-file header GenHpp/FilterNetworkDestination.h
//-only-file header //-
#pragma once
//-only-file body //-
//- #include "FilterNetworkDestination.h"


//- {include-body}
#include "MidiClientUtil.hpp" //- #include "MidiClientUtil.h"

//- {include-header}
#include "../genPrpt/FilterNetworkDestinationPrivate.hpp" //- #include "../genPrpt/FilterNetworkDestinationPrivate.h"
//-only-file header


//-var {PRE} "FilterNetworkDestination::"
class FilterNetworkDestination : public FilterNetworkDestinationPrivate

{
    Q_OBJECT

    QML_ELEMENT
public:
    //- {function} 1 1
    explicit FilterNetworkDestination(QObject *parent)
    //-only-file body
    : FilterNetworkDestinationPrivate{parent}
    {
        setFilterType( MidiRoutersFilterPrivate::FilterType::TO_NETWORK);
        setUuid(getUuId());
    };

    //- {fn}
    QJsonObject genJson() override
    //-only-file body
    {
        QJsonObject filterObj;
        filterObj["uuid"] = uuid();
        filterObj["filterType"] = static_cast<int>(filterType());
        filterObj["serverName"] = serverName();
        filterObj["serverPort"] = serverPort();
        filterObj["midiInputName"]= baseMidiRouteInput();
        return filterObj;
    }

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
