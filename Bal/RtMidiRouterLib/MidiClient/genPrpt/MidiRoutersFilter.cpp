#include "MidiRoutersFilter.h"

/*[[[cog
import cog
from MidiRoutersFilter import classMidiRoutersFilter


cog.outl(classMidiRoutersFilter.getClassCpp(),
        dedent=True, trimblanklines=True)


]]] */
 MidiRoutersFilter:: MidiRoutersFilter(QObject *parent)
    : QObject(parent)
{
    ctorClass();
}

//[[[end]]]

void MidiRoutersFilter::ctorClass() {}
