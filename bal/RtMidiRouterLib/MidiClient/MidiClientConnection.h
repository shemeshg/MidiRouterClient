#pragma once

#include "MidiClientConnectionPrivate.h"

class MidiClientConnection : public MidiClientConnectionPrivate

{
    Q_OBJECT    
    QML_ELEMENT
public:
    explicit MidiClientConnection(QObject *parent = nullptr);

public slots:
    void setServerStatusAndText(const ServerStatus &newServerStatus);

private:
   
};
