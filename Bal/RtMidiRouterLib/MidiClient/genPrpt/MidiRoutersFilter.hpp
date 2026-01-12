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

    
    MidiRoutersFilter(QObject *parent):MidiRoutersFilterPrivate(parent){}

    virtual ~MidiRoutersFilter() {
        
    }

    
enum class FilterType {
        TO_MIDI_DESTINATION, TO_CONSOLE, TO_NETWORK, SCHEDULE_TO, FILTER_AND_TRANSFORM, SWITCH_DATA1_DATA2
    };


    virtual QJsonObject genJson() = 0;

    //-only-file header
public slots:

private:
};
