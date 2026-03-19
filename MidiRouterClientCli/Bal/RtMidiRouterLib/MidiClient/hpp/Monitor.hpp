//-define-file body GenHpp/Monitor.cpp
//-define-file header GenHpp/Monitor.h
//-only-file header //-
#pragma once
#include <QJsonObject>
//-only-file body //-
//- #include "Monitor.h"
//- {include-header}
#include "../genPrpt/MonitorPrivate.hpp" //- #include "../genPrpt/MonitorPrivate.h"
//-only-file header


//-var {PRE} "Monitor::"
class Monitor : public MonitorPrivate

{
    Q_OBJECT
    QML_ELEMENT
public:
    //- {function} 1 1
    explicit Monitor(QObject *parent)
    //-only-file body
        : MonitorPrivate{parent}
    {
        setLogLen(2);
    };

    //- {fn}
    void addLogItem(const QString &newItem)
    //-only-file body
    {
        QStringList newLogItem = logItems();
        newLogItem.prepend(newItem);


        if (newLogItem.size() > logLen()) {
            newLogItem = newLogItem.mid(0, logLen());
        }

        setLogItems(newLogItem);
    }

    //- {fn}
    QJsonObject genJson()
    //-only-file body
    {
        QJsonObject monitor;
        monitor["isMonitored"] = isMonitored();
        monitor["logLen"] = logLen();
        return monitor;
    }

    //-only-file header
public slots:

private:
};
