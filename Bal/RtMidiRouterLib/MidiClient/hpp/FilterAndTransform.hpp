//-define-file body GenHpp/FilterAndTransform.cpp
//-define-file header GenHpp/FilterAndTransform.h
//-only-file header //-
#pragma once
//- #include "../genPrpt/FilterAndTransformPrivate.h"
//-only-file body //-
//- #include "FilterAndTransform.h"
//-only-file null
#include "../genPrpt/FilterAndTransformPrivate.hpp"
//-only-file header


//-var {PRE} "FilterAndTransform::"
class FilterAndTransform : public FilterAndTransformPrivate

{
    Q_OBJECT

    QML_ELEMENT
public:
    //- {function} 1 1
    explicit FilterAndTransform(QObject *parent = nullptr)
    //-only-file body
    : FilterAndTransformPrivate{parent}
    {
         setFilterType( FilterType::FILTER_AND_TRANSFORM);
    };

    //-only-file header
public slots:
    //- {fn}
    void setFilter(QString name, ConditionAction conditionAction, QString filterChannel,
                  QString filterEvents, QString filterData1, QString filterData2)
    //-only-file body
    {
        setName(name);
        setConditionAction(conditionAction);
        setFilterChannel(filterChannel);
        setFilterEvents(filterEvents);
        setFilterData1(filterData1);
        setFilterData2(filterData2);
    }

    //-only-file header
private:

};
