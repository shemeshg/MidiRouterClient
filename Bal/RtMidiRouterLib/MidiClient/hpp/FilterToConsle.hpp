//-define-file body GenHpp/FilterToConsle.cpp
//-define-file header GenHpp/FilterToConsle.h
//-only-file header //-
#pragma once
//- #include "../genPrpt/FilterToConslePrivate.h"
//-only-file body //-
//- #include "FilterToConsle.h"
//-only-file null
#include "../genPrpt/FilterToConslePrivate.hpp"
//-only-file header



//-var {PRE} "FilterToConsole::"
class FilterToConsole : public FilterToConslePrivate

{
    Q_OBJECT
    QML_ELEMENT
public:
    //- {function} 1 1
    explicit FilterToConsole(QObject *parent = nullptr)
    //-only-file body
    : FilterToConslePrivate{parent}
    {
         setFilterType( FilterType::TO_CONSOLE);
         setUserdata("{}");
    }

    //-only-file header
public slots:
    //- {function} 0 1
    void setFilter(LogTo logTo, QString userData)
    //-only-file body
    {
        setLogTo(logTo);
        setUserdata(userData);
        QString logToString = logTo == LogTo::CLIENT ? "Client" : "Server";
        setName("Log to " + logToString);
    }

    //-only-file header
private:

};

