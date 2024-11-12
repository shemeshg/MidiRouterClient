#include "MidiRouteInputPrivate.h"

/*[[[cog
import cog
from MidiRouteInputPrivate import classMidiRouteInputPrivate


cog.outl(classMidiRouteInputPrivate.getClassCpp(),
        dedent=True, trimblanklines=True)


]]] */
 MidiRouteInputPrivate:: MidiRouteInputPrivate(QObject *parent)
    : QObject(parent)
{
    ctorClass();
}

//[[[end]]]

void MidiRouteInputPrivate::ctorClass() {}
