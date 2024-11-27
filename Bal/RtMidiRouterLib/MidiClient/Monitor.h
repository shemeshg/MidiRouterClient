

#pragma once
#include "MonitorPrivate.h"


class Monitor : public MonitorPrivate

{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit Monitor(QObject *parent = nullptr)
        : MonitorPrivate{parent} {};







public slots:

private:
};
