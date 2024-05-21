#include "BalDataPrivate.h"

/*[[[cog
import cog
from BalDataPrivate import classBalDataPrivate


cog.outl(classBalDataPrivate.getClassCpp(),
        dedent=True, trimblanklines=True)


]]] */
 BalDataPrivate:: BalDataPrivate(QObject *parent)
    : JsAsync(parent)
{
    ctorClass();
}

//[[[end]]]

void BalDataPrivate::ctorClass()
{

}
