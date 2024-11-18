#pragma once

#include "FilterToConslePrivate.h"

class FilterToConsole : public FilterToConslePrivate

{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit FilterToConsole(QObject *parent = nullptr){

    };

public slots:
    void setFilter(LogTo logTo, QString userData){
        setLogTo(logTo);
        setUserdata(userData);
        QString logToString = logTo == LogTo::CLIENT ? "Client" : "Server";
        setName("Log to " + logToString);
    }

private:

};
