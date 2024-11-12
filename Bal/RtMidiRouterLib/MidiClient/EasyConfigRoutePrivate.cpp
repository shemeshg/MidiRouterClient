#include "EasyConfigRoutePrivate.h"

/*[[[cog
import cog
from EasyConfigRoutePrivate import classEasyConfigRoutePrivate


cog.outl(classEasyConfigRoutePrivate.getClassCpp(),
        dedent=True, trimblanklines=True)


]]] */
 EasyConfigRoutePrivate:: EasyConfigRoutePrivate(QObject *parent)
    : QObject(parent)
{
    ctorClass();
}

//[[[end]]]

void EasyConfigRoutePrivate::ctorClass() {}
