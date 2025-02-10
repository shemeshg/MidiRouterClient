#line 8 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/FilterMidiDestination.hpp"
#include "FilterMidiDestination.h"
     FilterMidiDestination::FilterMidiDestination(QObject * parent) 
#line 24 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/FilterMidiDestination.hpp"
    : FilterMidiDestinationPrivate{parent}
    {
        setFilterType( FilterType::TO_MIDI_DESTINATION); 
    };

    void FilterMidiDestination::setFilter(QString input) 
#line 34 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/FilterMidiDestination.hpp"
    {
        setBaseMidiRouteInput(input); 
        setName("To midi " + input); 
    }

