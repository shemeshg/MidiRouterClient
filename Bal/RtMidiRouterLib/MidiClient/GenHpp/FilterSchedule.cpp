#include "FilterSchedule.h"
     FilterSchedule::FilterSchedule(QObject *parent) 
    : FilterSchedulePrivate{parent}
    {
    };

    void FilterSchedule::setFilter(DefferedType defferedType, int defferedTo ) 
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

