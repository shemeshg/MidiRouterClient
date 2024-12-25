#include "FilterToConsle.h"
     FilterToConsole::FilterToConsole(QObject *parent) 
    : FilterToConslePrivate{parent}
    {
    }

    void FilterToConsole::setFilter(LogTo logTo, QString userData) 
    {
        setLogTo(logTo);
        setUserdata(userData);
        QString logToString = logTo == LogTo::CLIENT ? "Client" : "Server";
        setName("Log to " + logToString);
    }
