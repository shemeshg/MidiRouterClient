#include "FilterMidiDestinationPrivate.h"

/*[[[cog
import cog
from FilterMidiDestinationPrivate import prptClass


cog.outl(prptClass.getClassCpp(),
        dedent=True, trimblanklines=True)


]]] */
 FilterMidiDestinationPrivate:: FilterMidiDestinationPrivate(QObject *parent)
    : MidiRoutersFilter(parent)
{
    ctorClass();
}

//[[[end]]]

void FilterMidiDestinationPrivate::ctorClass() {
    setFilterType( FilterType::TO_MIDI_DESTINATION);
}
