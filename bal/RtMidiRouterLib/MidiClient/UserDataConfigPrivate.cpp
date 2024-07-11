#include "UserDataConfigPrivate.h"

/*[[[cog
import cog
from UserDataConfigPrivate import classUserDataConfigPrivate


cog.outl(classUserDataConfigPrivate.getClassCpp(),
        dedent=True, trimblanklines=True)


]]] */
 UserDataConfigPrivate:: UserDataConfigPrivate(QObject *parent)
    : QObject(parent)
{
    ctorClass();
}

//[[[end]]]

void UserDataConfigPrivate::ctorClass() {}
