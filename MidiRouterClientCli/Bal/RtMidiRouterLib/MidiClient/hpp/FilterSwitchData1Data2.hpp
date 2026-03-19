


//-define-file body GenHpp/FilterSwitchData1Data2.cpp
//-define-file header GenHpp/FilterSwitchData1Data2.h
//-only-file header //-
#pragma once
//-only-file body //-
//- #include "FilterSwitchData1Data2.h"
//- {include-header}
#include "../genPrpt/FilterSwitchData1Data2Private.hpp" //- #include "../genPrpt/FilterSwitchData1Data2Private.h"
//- {include-body}
#include "MidiClientUtil.hpp" //- #include "MidiClientUtil.h"



//-only-file header
//-var {PRE} "FilterSwitchData1Data2::"
class FilterSwitchData1Data2 : public FilterSwitchData1Data2Private

{
    Q_OBJECT

    QML_ELEMENT
public:
    //- {function} 1 1
    explicit FilterSwitchData1Data2(QObject *parent)
    //-only-file body
    : FilterSwitchData1Data2Private{parent}
    {

        setFilterType( MidiRoutersFilterPrivate::FilterType::SWITCH_DATA1_DATA2);
        setUuid(getUuId());
    };

    //- {fn}
    QJsonObject genJson() override
    //-only-file body
    {
        QJsonObject filterObj;
        filterObj["uuid"] = uuid();
        filterObj["filterType"] = static_cast<int>(filterType());
        return filterObj;

    }

    //-only-file header
public slots:
    //- {fn}
    void setFilter(QString input)
    //-only-file body
    {
        setName("SWITCH DATA1 DATA2");
    }

    //-only-file header
private:

};
