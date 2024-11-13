

#pragma once
#include "UserControlPrivate.h"

class UserControl : public UserControlPrivate

{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit UserControl(QObject *parent = nullptr)
        : UserControlPrivate{parent} {};

public slots:

private:
};
