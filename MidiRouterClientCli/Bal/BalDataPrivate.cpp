#include "BalDataPrivate.h"

/*[[[cog
import cog
from BalDataPrivate import classBalDataPrivate


cog.outl(classBalDataPrivate.getClassCpp(),
        dedent=True, trimblanklines=True)


]]] */
 BalDataPrivate:: BalDataPrivate(QObject *parent)
    : QObject(parent)
{
    ctorClass();
}

//[[[end]]]

void BalDataPrivate::ctorClass()
{
    //m_isServerRunning = false;
    //m_serverPort = -1;
}
