//-define-file body GenHpp/MidiClientConnection.cpp
//-define-file header GenHpp/MidiClientConnection.h
//-only-file header //-
//-only-file body //-
//- #include "MidiClientConnection.h"
//-only-file null
//-only-file header
#pragma once

#include "../genPrpt/MidiClientConnectionPrivate.h"

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
    //- {function} 0 1
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
