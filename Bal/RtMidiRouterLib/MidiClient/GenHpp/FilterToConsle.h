#pragma once
#include "../genPrpt/FilterToConslePrivate.h"


class FilterToConsole : public FilterToConslePrivate

{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit FilterToConsole(QObject *parent = nullptr);
public slots:
    void setFilter(LogTo logTo, QString userData);
private:

};

