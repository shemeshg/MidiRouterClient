#include "UserControlPrivate.h"

/*[[[cog
import cog
from UserControlPrivate import classUserControlPrivate


cog.outl(classUserControlPrivate.getClassCpp(),
        dedent=True, trimblanklines=True)


]]] */
 EasyConfigRoutePrivate:: EasyConfigRoutePrivate(QObject *parent)
    : QObject(parent)
{
    ctorClass();
}

//[[[end]]]

void UserControlPrivate::ctorClass() {}
