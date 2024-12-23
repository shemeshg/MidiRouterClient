#include "PresetMidiControlPrivate.h"

/*[[[cog
import cog
from PresetMidiControlPrivate import prptClass


cog.outl(prptClass.getClassCpp(),
        dedent=True, trimblanklines=True)


]]] */
 PresetMidiControlPrivate:: PresetMidiControlPrivate(QObject *parent)
    : QObject(parent)
{
    ctorClass();
}

//[[[end]]]

void PresetMidiControlPrivate::ctorClass() {
    m_channel = -1;
    m_data1 = -1;
    m_data2 = -1;
}
