

#pragma once
#include "genPrpt/UserControlPrivate.h"

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
