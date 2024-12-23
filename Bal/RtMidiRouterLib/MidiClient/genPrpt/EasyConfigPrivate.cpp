#include "EasyConfigPrivate.h"

/*[[[cog
import cog
from EasyConfigPrivate import prptClass


cog.outl(prptClass.getClassCpp(),
        dedent=True, trimblanklines=True)


]]] */
 EasyConfigPrivate:: EasyConfigPrivate(QObject *parent)
    : QObject(parent)
{
    ctorClass();
}

//[[[end]]]

void EasyConfigPrivate::ctorClass() {}
