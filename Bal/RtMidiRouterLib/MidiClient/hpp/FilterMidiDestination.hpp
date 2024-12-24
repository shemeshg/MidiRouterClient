//-define-file body GenHpp/FilterMidiDestination.cpp
//-define-file header GenHpp/FilterMidiDestination.h
//-only-file header //-
//-only-file body //-
//- #include "FilterMidiDestination.h"
//-only-file null
//-only-file header
#pragma once

#include "../genPrpt/FilterMidiDestinationPrivate.h"

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
    };

    //-only-file header
public slots:
    //- {function} 0 1
    void setFilter(QString input)
    //-only-file body
    {
        setBaseMidiRouteInput(input);
        setName("To midi " + input);
    }

    //-only-file header
private:

};
