#include "UserDataConfigPrivate.h"

/*[[[cog
import cog
from UserDataConfigPrivate import prptClass


cog.outl(prptClass.getClassCpp(),
        dedent=True, trimblanklines=True)


]]] */
 UserDataConfigPrivate:: UserDataConfigPrivate(QObject *parent)
    : QObject(parent)
{
    ctorClass();
}

//[[[end]]]

void UserDataConfigPrivate::ctorClass() {}
