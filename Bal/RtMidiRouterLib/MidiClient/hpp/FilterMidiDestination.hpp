//-define-file body GenHpp/FilterMidiDestination.cpp
//-define-file header GenHpp/FilterMidiDestination.h
//-only-file header //-
#pragma once
//- #include "../genPrpt/FilterMidiDestinationPrivate.h"

//-only-file body //-
//- #include "FilterMidiDestination.h"
//-only-file null
#include "../genPrpt/FilterMidiDestinationPrivate.hpp"
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
    };

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
