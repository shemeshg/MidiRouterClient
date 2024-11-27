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

void MidiRouteInputPrivate::ctorClass() {
     m_ignoreTypesMidiSysex = true;
     m_ignoreTypesMidiTime = true;
    m_ignoreTypesMidiSense = true;
     m_midiRouteClockTimeSig = 4;
    m_midiRouteClockTimeSigDivBy = 4;
    m_midiRouteClockFromSppPos = 0;
    m_monitor = new Monitor();
}
