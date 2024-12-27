#include "FilterAndTransform.h"
     FilterAndTransform::FilterAndTransform(QObject * parent) 
    : FilterAndTransformPrivate{parent}
    {
    };

    void FilterAndTransform::setFilter(QString name, ConditionAction conditionAction, QString filterChannel, QString filterEvents, QString filterData1, QString filterData2) 
    {
        setName(name);
        setConditionAction(conditionAction);
        setFilterChannel(filterChannel);
        setFilterEvents(filterEvents);
        setFilterData1(filterData1);
        setFilterData2(filterData2);
    }

