

#pragma once
#include "EasyConfigRoutePrivate.h"

class EasyConfigRoute : public EasyConfigRoutePrivate

{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit EasyConfigRoute(QObject *parent = nullptr)
        : EasyConfigRoutePrivate{parent} {};

public slots:

private:
};
