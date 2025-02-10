//-define-file body GenHpp/MidiClientConnection.cpp
//-define-file header GenHpp/MidiClientConnection.h
//-only-file header //-
#pragma once
//- #include "../genPrpt/MidiClientConnectionPrivate.h"
//-only-file body //-
//- #include "MidiClientConnection.h"
//-only-file null
#include "../genPrpt/MidiClientConnectionPrivate.hpp"
//-only-file header

//-var {PRE} "MidiClientConnection::"
class MidiClientConnection : public MidiClientConnectionPrivate

{
    Q_OBJECT

    QML_ELEMENT
public:
    //- {function} 1 1
    explicit MidiClientConnection(QObject *parent = nullptr)
    //-only-file body
    : MidiClientConnectionPrivate{parent}
    {
        setServerStatusAndText(ServerStatus::STOPPED);
        m_userDataConfig = new UserDataConfig(this);
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
