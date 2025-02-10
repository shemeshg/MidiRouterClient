#line 7 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/MidiClientConnection.hpp"
#include "MidiClientConnection.h"
     MidiClientConnection::MidiClientConnection(QObject * parent) 
#line 23 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/MidiClientConnection.hpp"
    : MidiClientConnectionPrivate{parent}
    {
        setServerStatusAndText(ServerStatus::STOPPED);
        m_userDataConfig = new UserDataConfig(this);
    }

    void MidiClientConnection::setServerStatusAndText(const ServerStatus &newServerStatus) 
#line 34 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/MidiClientConnection.hpp"
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

