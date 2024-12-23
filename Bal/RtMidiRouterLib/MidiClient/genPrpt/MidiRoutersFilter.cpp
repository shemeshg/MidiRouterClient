#include "MidiRoutersFilter.h"

/*[[[cog
import cog
from MidiRoutersFilter import prptClass


cog.outl(prptClass.getClassCpp(),
        dedent=True, trimblanklines=True)


]]] */
 MidiRoutersFilter:: MidiRoutersFilter(QObject *parent)
    : QObject(parent)
{
    ctorClass();
}

//[[[end]]]

void MidiRoutersFilter::ctorClass() {}
