//-define-file body GenHpp/FilterMidiDestination.cpp
//-define-file header GenHpp/FilterMidiDestination.h
//-only-file header //-
#pragma once
//-only-file body //-
//- #include "FilterMidiDestination.h"
//- {include-header}
#include "../genPrpt/FilterMidiDestinationPrivate.hpp" //- #include "../genPrpt/FilterMidiDestinationPrivate.h"
//- {include-body}
#include "MidiClientUtil.hpp" //- #include "MidiClientUtil.h"



//-only-file header
//-var {PRE} "FilterMidiDestination::"
class FilterMidiDestination : public FilterMidiDestinationPrivate

{
    Q_OBJECT

    QML_ELEMENT
public:
    //- {function} 1 1
    explicit FilterMidiDestination(QObject *parent = nullptr)
    //-only-file body
    : FilterMidiDestinationPrivate{parent}
    {
        setFilterType( FilterType::TO_MIDI_DESTINATION);
        setUuid(getUuId());
    };

    //- {fn}
    QJsonObject getJson() override
    //-only-file body
    {
        QJsonObject filterObj;
        filterObj["uuid"] = uuid();
        filterObj["filterType"] = static_cast<int>(filterType());
        filterObj["midiInputName"]= baseMidiRouteInput();
        return filterObj;

    }

    //-only-file header
public slots:
    //- {fn}
    void setFilter(QString input)
    //-only-file body
    {
        setBaseMidiRouteInput(input);
        setName("To midi " + input);
    }

    //-only-file header
private:

};
