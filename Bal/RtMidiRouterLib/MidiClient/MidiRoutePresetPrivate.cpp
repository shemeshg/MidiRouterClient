#include "MidiRoutePresetPrivate.h"

/*[[[cog
import cog
from MidiRoutePresetPrivate import classMidiRoutePresetPrivate


cog.outl(classMidiRoutePresetPrivate.getClassCpp(),
        dedent=True, trimblanklines=True)


]]] */
 MidiRoutePresetPrivate:: MidiRoutePresetPrivate(QObject *parent)
    : QObject(parent)
{
    ctorClass();
}

//[[[end]]]

void MidiRoutePresetPrivate::ctorClass() {}
