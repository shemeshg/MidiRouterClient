#pragma once
#include "UserDataConfigPrivate.h"

class UserDataConfig : public UserDataConfigPrivate

{
    Q_OBJECT    
    QML_ELEMENT
public:
    explicit UserDataConfig(QObject *parent = nullptr);

    virtual ~UserDataConfig() { clearDropdownlists(); }

public slots:

private:
    void loadComputerUuid();
    void clearDropdownlists();
};
