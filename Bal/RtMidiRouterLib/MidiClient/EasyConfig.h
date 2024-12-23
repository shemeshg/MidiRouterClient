

#pragma once
#include "EasyConfigPrivate.h"
#include "EasyConfigRoute.h"

class EasyConfig : public EasyConfigPrivate

{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit EasyConfig(QObject *parent = nullptr)
        : EasyConfigPrivate{parent} {};







public slots:

private:
};
