#pragma once
#include "../genPrpt/EasyConfigPrivate.h"

class EasyConfig : public EasyConfigPrivate

{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit EasyConfig(QObject *parent = nullptr);
public slots:

private:
};
