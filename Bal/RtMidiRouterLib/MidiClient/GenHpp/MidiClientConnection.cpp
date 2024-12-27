#include "MidiClientConnection.h"
     MidiClientConnection::MidiClientConnection(QObject * parent) 
    : MidiClientConnectionPrivate{parent}
    {
        setServerStatusAndText(ServerStatus::STOPPED);
    }

    void MidiClientConnection::setServerStatusAndText(const ServerStatus &newServerStatus) 
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

