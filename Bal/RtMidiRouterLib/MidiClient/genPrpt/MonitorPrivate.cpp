#include "MonitorPrivate.h"

/*[[[cog
import cog
from MonitorPrivate import classMonitorPrivate


cog.outl(classMonitorPrivate.getClassCpp(),
        dedent=True, trimblanklines=True)


]]] */
 MonitorPrivate:: MonitorPrivate(QObject *parent)
    : QObject(parent)
{
    ctorClass();
}

//[[[end]]]

void MonitorPrivate::ctorClass() {}
