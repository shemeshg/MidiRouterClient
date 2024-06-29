#include "MidiClientConnection.h"

/*[[[cog
import cog
from MidiClientConnection import classMidiClientConnection


cog.outl(classMidiClientConnection.getClassCpp(),
        dedent=True, trimblanklines=True)


]]] */
 MidiClientConnection:: MidiClientConnection(QObject *parent)
    : QObject(parent)
{
    ctorClass();
}

//[[[end]]]

void MidiClientConnection::ctorClass()
{
    m_serverStatusText = "Not Connected";
}
