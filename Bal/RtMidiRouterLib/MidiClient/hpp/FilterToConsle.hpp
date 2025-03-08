//-define-file body GenHpp/FilterToConsle.cpp
//-define-file header GenHpp/FilterToConsle.h
//-only-file header //-
#pragma once
//-only-file body //-
//- #include "FilterToConsle.h"
//- {include-body}
#include "MidiClientUtil.hpp" //- #include "MidiClientUtil.h"
//- {include-header}
#include "../genPrpt/FilterToConslePrivate.hpp" //- #include "../genPrpt/FilterToConslePrivate.h"
//-only-file header



//-var {PRE} "FilterToConsole::"
class FilterToConsole : public FilterToConslePrivate

{
    Q_OBJECT
    QML_ELEMENT
public:
    //- {function} 1 1
    explicit FilterToConsole(QObject *parent)
    //-only-file body
    : FilterToConslePrivate{parent}
    {
         setFilterType( FilterType::TO_CONSOLE);
         setUserdata("{}");
         setUuid(getUuId());
    }

    //- {fn}
    QJsonObject genJson() override
    //-only-file body
    {
        QJsonObject filterObj;

        filterObj["uuid"] = uuid();
        filterObj["filterType"] = static_cast<int>(filterType());
        filterObj["logTo"] = static_cast<int>(logTo());
        filterObj["userdata"] = userdata();
        return filterObj;
    }

    //-only-file header
public slots:
    //- {fn}
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

