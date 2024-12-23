#include "Dropdownlist.h"

/*[[[cog
import cog
from Dropdownlist import prptClass


cog.outl(prptClass.getClassCpp(),
        dedent=True, trimblanklines=True)


]]] */
 Dropdownlist:: Dropdownlist(QObject *parent)
    : QObject(parent)
{
    ctorClass();
}

//[[[end]]]

void Dropdownlist::ctorClass() {}
