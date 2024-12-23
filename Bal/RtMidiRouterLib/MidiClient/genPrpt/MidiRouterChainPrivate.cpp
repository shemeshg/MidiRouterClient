#include "MidiRouterChainPrivate.h"

/*[[[cog
import cog
from MidiRouterChainPrivate import prptClass


cog.outl(prptClass.getClassCpp(),
        dedent=True, trimblanklines=True)


]]] */
 MidiRouterChainPrivate:: MidiRouterChainPrivate(QObject *parent)
    : QObject(parent)
{
    ctorClass();
}

//[[[end]]]

void MidiRouterChainPrivate::ctorClass() {}
