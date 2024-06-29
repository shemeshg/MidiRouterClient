#include "MidiClientConnection.h"

MidiClientConnection::MidiClientConnection(QObject *parent)
    : MidiClientConnectionPrivate{parent}
{
    setServerStatusAndText(ServerStatus::Stopped);
}

void MidiClientConnection::setServerStatusAndText(const ServerStatus &newServerStatus)
{
    setServerStatus(newServerStatus);
    if (newServerStatus == ServerStatus::Stopped) {
        setServerStatusText("Stopped");
    } else if (newServerStatus == ServerStatus::Starting) {
        setServerStatusText("Starting");
    } else if (newServerStatus == ServerStatus::Running) {
        setServerStatusText("Running");
    } else {
        setServerStatusText("Failed");
    }
}
