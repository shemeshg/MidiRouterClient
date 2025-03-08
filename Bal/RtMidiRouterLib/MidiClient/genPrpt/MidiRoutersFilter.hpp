//-define-file body genPrpt/MidiRoutersFilter.cpp
//-define-file header genPrpt/MidiRoutersFilter.h
//-only-file header //-
#pragma once
#include <QJsonObject>

//-only-file body //-
//- #include "MidiRoutersFilter.h"

//- {include-header}
#include "MidiRoutersFilterPrivate.hpp"  //- #include "../genPrpt/MidiRoutersFilterPrivate.h"



//-only-file header


//-var {PRE} "MidiRoutersFilter::"
class MidiRoutersFilter : public MidiRoutersFilterPrivate

{
    Q_OBJECT
    QML_ELEMENT
public:
<<<<<<< HEAD
    //- {function} 1 1
    explicit MidiRoutersFilter(QObject *parent = nullptr)
    //-only-file body
        : MidiRoutersFilterPrivate{parent}
    {
=======
    
    MidiRoutersFilter(QObject *parent):QObject(parent){}

    virtual ~MidiRoutersFilter() {
        
    }

    
enum class FilterType {
        TO_MIDI_DESTINATION, TO_CONSOLE, TO_NETWORK, SCHEDULE_TO, FILTER_AND_TRANSFORM
>>>>>>> e1c2bc8 (memory parent issues)
    };

    //-only-file header
    virtual ~MidiRoutersFilter(){}

    virtual QJsonObject genJson() = 0;

    //-only-file header
public slots:

private:
};
