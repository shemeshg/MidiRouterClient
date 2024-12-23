#include "MidiRouteInputCc14bit.h"

/*[[[cog
import cog
from MidiRouteInputCc14bit import prptClass


cog.outl(prptClass.getClassCpp(),
        dedent=True, trimblanklines=True)


]]] */
 MidiRouteInputCc14bit:: MidiRouteInputCc14bit(QObject *parent)
    : QObject(parent)
{
    ctorClass();
}

//[[[end]]]

void MidiRouteInputCc14bit::ctorClass() {}
