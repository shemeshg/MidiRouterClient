//-define-file body GenHpp/Monitor.cpp
//-define-file header GenHpp/Monitor.h
//-only-file header //-
#pragma once
//- #include "../genPrpt/MonitorPrivate.h"
//-only-file body //-
//- #include "Monitor.h"
//-only-file null
#include "../genPrpt/MonitorPrivate.hpp"
//-only-file header


//-var {PRE} "Monitor::"
class Monitor : public MonitorPrivate

{
    Q_OBJECT
    QML_ELEMENT
public:
    //- {function} 1 1
    explicit Monitor(QObject *parent = nullptr)
    //-only-file body
        : MonitorPrivate{parent}
    {
    };

    //-only-file header
public slots:

private:
};
