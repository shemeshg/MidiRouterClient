//-define-file body GenHpp/MidiClientConnection.cpp
//-define-file header GenHpp/MidiClientConnection.h
//-only-file header //-
#pragma once

//-only-file body //-
//- #include "MidiClientConnection.h"
//- {include-header}
#include "../genPrpt/MidiClientConnectionPrivate.hpp" //- #include "../genPrpt/MidiClientConnectionPrivate.h"
//-only-file header

//-var {PRE} "MidiClientConnection::"
class MidiClientConnection : public MidiClientConnectionPrivate

{
    Q_OBJECT

    QML_ELEMENT
public:
    //- {function} 1 1
    explicit MidiClientConnection(QObject *parent)
    //-only-file body
    : MidiClientConnectionPrivate{parent}
    {
        setServerStatusAndText(ServerStatus::STOPPED);        
    }

    //-only-file header
public slots:
    //- {fn}
    void setServerStatusAndText(const ServerStatus &newServerStatus)
    //-only-file body
    {
        setServerStatus(newServerStatus);
        if (newServerStatus == ServerStatus::STOPPED) {
            setServerStatusText("Stopped");
        } else if (newServerStatus == ServerStatus::STARTING) {
            setServerStatusText("Starting");
        } else if (newServerStatus == ServerStatus::RUNNING) {
            setServerStatusText("Running");
        } else {
            setServerStatusText("Failed");
        }
    }

    //-only-file header
private:        

};
