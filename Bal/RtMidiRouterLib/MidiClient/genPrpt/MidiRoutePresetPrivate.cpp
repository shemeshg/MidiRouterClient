#include "MidiRoutePresetPrivate.h"

/*[[[cog
import cog
from MidiRoutePresetPrivate import prptClass


cog.outl(prptClass.getClassCpp(),
        dedent=True, trimblanklines=True)


]]] */
 MidiRoutePresetPrivate:: MidiRoutePresetPrivate(QObject *parent)
    : QObject(parent)
{
    ctorClass();
}

//[[[end]]]

void MidiRoutePresetPrivate::ctorClass() {}
