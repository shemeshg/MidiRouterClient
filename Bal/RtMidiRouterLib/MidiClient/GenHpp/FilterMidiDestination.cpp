#include "FilterMidiDestination.h"
     FilterMidiDestination::FilterMidiDestination(QObject * parent) 
    : FilterMidiDestinationPrivate{parent}
    {
    };

    void FilterMidiDestination::setFilter(QString input) 
    {
        setBaseMidiRouteInput(input);
        setName("To midi " + input);
    }

