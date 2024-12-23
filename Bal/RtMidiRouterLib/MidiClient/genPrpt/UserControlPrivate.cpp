#include "UserControlPrivate.h"

/*[[[cog
import cog
from UserControlPrivate import prptClass


cog.outl(prptClass.getClassCpp(),
        dedent=True, trimblanklines=True)


]]] */
 UserControlPrivate:: UserControlPrivate(QObject *parent)
    : QObject(parent)
{
    ctorClass();
}

//[[[end]]]

void UserControlPrivate::ctorClass() {}
