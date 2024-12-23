#pragma once

#include "genPrpt/FilterMidiDestinationPrivate.h"

class FilterMidiDestination : public FilterMidiDestinationPrivate

{
    Q_OBJECT

    QML_ELEMENT
public:
    explicit FilterMidiDestination(QObject *parent = nullptr){

    };

public slots:
    void setFilter(QString input){
        setBaseMidiRouteInput(input);
        setName("To midi " + input);
    }

private:

};
