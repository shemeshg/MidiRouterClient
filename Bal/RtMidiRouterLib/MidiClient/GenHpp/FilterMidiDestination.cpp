#include "FilterMidiDestination.h"
     FilterMidiDestination::FilterMidiDestination(QObject * parent) 
    : FilterMidiDestinationPrivate{parent}
    {
        setFilterType( FilterType::TO_MIDI_DESTINATION);
    };

    void FilterMidiDestination::setFilter(QString input) 
    {
        setBaseMidiRouteInput(input);
        setName("To midi " + input);
    }

