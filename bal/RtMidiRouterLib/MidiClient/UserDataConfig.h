#pragma once

#include "UserDataConfigPrivate.h"

class UserDataConfig : public UserDataConfigPrivate

{
    Q_OBJECT    
    QML_ELEMENT
public:
    explicit UserDataConfig(QObject *parent = nullptr):UserDataConfigPrivate{parent}{
        setActivePresetID(0);
    }

public slots:


private:
   
};
