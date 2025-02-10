#pragma once
#include "../genPrpt/MidiClientConnectionPrivate.h"

class MidiClientConnection : public MidiClientConnectionPrivate

{
    Q_OBJECT

    QML_ELEMENT
public:
#line 21 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/MidiClientConnection.hpp"
    explicit MidiClientConnection(QObject *parent = nullptr);
public slots:
#line 32 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/MidiClientConnection.hpp"
    void setServerStatusAndText(const ServerStatus &newServerStatus);
private:        

};
