//-define-file body GenHpp/FilterAndTransform.cpp
//-define-file header GenHpp/FilterAndTransform.h
//-only-file header //-
#pragma once
//-only-file body //-
//- #include "FilterAndTransform.h"
//- {include-header}
#include "../genPrpt/FilterAndTransformPrivate.hpp" //- #include "../genPrpt/FilterAndTransformPrivate.h"
//- {include-body}
#include "MidiClientUtil.hpp" //- #include "MidiClientUtil.h"



//-only-file header
//-var {PRE} "FilterAndTransform::"
class FilterAndTransform : public FilterAndTransformPrivate

{
    Q_OBJECT

    QML_ELEMENT
public:
    //- {function} 1 1
    explicit FilterAndTransform(QObject *parent)
    //-only-file body
    : FilterAndTransformPrivate{parent}
    {
         setFilterType( MidiRoutersFilterPrivate::FilterType::FILTER_AND_TRANSFORM);
        setUuid(getUuId());
    };

    //- {fn}
    QJsonObject genJson() override
    //-only-file body
    {
        QJsonObject filterObj;
        filterObj["uuid"] = uuid();
        filterObj["filterType"] = static_cast<int>(filterType());
        filterObj["name"] = name();
        filterObj["conditionAction"] = static_cast<int>(conditionAction());
        filterObj["filterChannel"] = filterChannel();
        filterObj["filterEvents"] = filterEvents();
        filterObj["filterData1"] = filterData1();
        filterObj["filterData2"] = filterData2();
        return filterObj;

    }

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
