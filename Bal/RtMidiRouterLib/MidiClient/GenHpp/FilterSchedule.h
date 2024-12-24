#pragma once

#include "../genPrpt/FilterSchedulePrivate.h"

class FilterSchedule : public FilterSchedulePrivate

{
    Q_OBJECT

    QML_ELEMENT
public:
    explicit FilterSchedule(QObject *parent = nullptr);
public slots:
    void setFilter(DefferedType defferedType, int defferedTo );
private:

};
