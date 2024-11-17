#include "FilterMidiDestinationPrivate.h"

/*[[[cog
import cog
from FilterMidiDestinationPrivate import classFilterMidiDestinationPrivate


cog.outl(classFilterMidiDestinationPrivate.getClassCpp(),
        dedent=True, trimblanklines=True)


]]] */
 FilterMidiDestinationPrivate:: FilterMidiDestinationPrivate(QObject *parent)
    : MidiRoutersFilter(parent)
{
    ctorClass();
}

//[[[end]]]

void FilterMidiDestinationPrivate::ctorClass() {
    m_filterType = FilterType::TO_MIDI_DESTINATION;
}
