#include "PresetMidiControlPrivate.h"

/*[[[cog
import cog
from PresetMidiControlPrivate import classPresetMidiControlPrivate


cog.outl(classPresetMidiControlPrivate.getClassCpp(),
        dedent=True, trimblanklines=True)


]]] */
 PresetMidiControlPrivate:: PresetMidiControlPrivate(QObject *parent)
    : QObject(parent)
{
    m_channel = -1;
    ctorClass();
}

//[[[end]]]

void PresetMidiControlPrivate::ctorClass() {}
