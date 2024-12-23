#include "MidiClientConnectionPrivate.h"

/*[[[cog
import cog
from MidiClientConnectionPrivate import prptClass


cog.outl(prptClass.getClassCpp(),
        dedent=True, trimblanklines=True)


]]] */
 MidiClientConnectionPrivate:: MidiClientConnectionPrivate(QObject *parent)
    : QObject(parent)
{
    ctorClass();
}

//[[[end]]]

void MidiClientConnectionPrivate::ctorClass() {
    m_userDataConfig = new UserDataConfig(this);

}
