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
    //- {function} 1 1
    explicit MidiRoutersFilter(QObject *parent = nullptr)
    //-only-file body
        : MidiRoutersFilterPrivate{parent}
    {
    };

    //-only-file header
public slots:

private:
};
