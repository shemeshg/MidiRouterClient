//-define-file body GenHpp/FilterSchedule.cpp
//-define-file header GenHpp/FilterSchedule.h
//-only-file header //-
//-only-file body //-
//- #include "FilterSchedule.h"
//-only-file null
//-only-file header
#pragma once

#include "../genPrpt/FilterSchedulePrivate.h"

//-var {PRE} "FilterSchedule::"
class FilterSchedule : public FilterSchedulePrivate

{
    Q_OBJECT

    QML_ELEMENT
public:
    //- {function} 1 1
    explicit FilterSchedule(QObject *parent = nullptr)
    //-only-file body
    : FilterSchedulePrivate{parent}
    {
    };

    //-only-file header
public slots:
    //- {function} 0 1
    void setFilter(DefferedType defferedType, int defferedTo )
    //-only-file body
    {
        setDefferedType(defferedType);
        setDefferedTo(defferedTo);

        QMap<DefferedType, QString> defferedTypeToString = {
            {DefferedType::IN_SPP, "IN_SPP"},
            {DefferedType::IN_BAR, "IN_BAR"},
            {DefferedType::AT_SPP_AT_BAR, "AT_SPP_AT_BAR"},
            {DefferedType::QUANTIZE_SPP, "QUANTIZE_SPP"},
            {DefferedType::QUANTIZE_BAR, "QUANTIZE_BAR"}
        };

        setName(
            QString("Schedule %1 %2").arg(defferedTypeToString.value(defferedType)).arg(defferedTo)
            );
    }

    //-only-file header
private:

};