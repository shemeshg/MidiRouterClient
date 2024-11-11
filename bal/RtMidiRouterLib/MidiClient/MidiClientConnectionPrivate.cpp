#include "MidiClientConnectionPrivate.h"

/*[[[cog
import cog
from MidiClientConnectionPrivate import classMidiClientConnectionPrivate


cog.outl(classMidiClientConnectionPrivate.getClassCpp(),
        dedent=True, trimblanklines=True)


]]] */
 MidiClientConnectionPrivate:: MidiClientConnectionPrivate(QObject *parent)
    : QObject(parent)
{
    ctorClass();
}

//[[[end]]]

void MidiClientConnectionPrivate::ctorClass() {
    m_userDataConfig = new UserDataConfig();
}
