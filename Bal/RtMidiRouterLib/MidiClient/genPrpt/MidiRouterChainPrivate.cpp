#include "MidiRouterChainPrivate.h"

/*[[[cog
import cog
from MidiRouterChainPrivate import classMidiRouterChainPrivate


cog.outl(classMidiRouterChainPrivate.getClassCpp(),
        dedent=True, trimblanklines=True)


]]] */
 MidiRouterChainPrivate:: MidiRouterChainPrivate(QObject *parent)
    : QObject(parent)
{
    ctorClass();
}

//[[[end]]]

void MidiRouterChainPrivate::ctorClass() {}
