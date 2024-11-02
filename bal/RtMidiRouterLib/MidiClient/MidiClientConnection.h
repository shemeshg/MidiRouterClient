#pragma once

#include "MidiClientConnectionPrivate.h"
#include "UserDataConfig.h"

class MidiClientConnection : public MidiClientConnectionPrivate

{
    Q_OBJECT
    Q_PROPERTY(UserDataConfig *userDataConfig READ userDataConfig CONSTANT)
    QML_ELEMENT
public:
    explicit MidiClientConnection(QObject *parent = nullptr);
    UserDataConfig *userDataConfig() { return &m_userDataConfig; }

public slots:
    void setServerStatusAndText(const ServerStatus &newServerStatus);

private:        
    UserDataConfig m_userDataConfig{};
};
