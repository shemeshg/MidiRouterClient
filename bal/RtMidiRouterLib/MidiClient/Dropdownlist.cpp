#include "Dropdownlist.h"

/*[[[cog
import cog
from Dropdownlist import classDropdownlist


cog.outl(classDropdownlist.getClassCpp(),
        dedent=True, trimblanklines=True)


]]] */
 Dropdownlist:: Dropdownlist(QObject *parent)
    : QObject(parent)
{
    ctorClass();
}

//[[[end]]]

void Dropdownlist::ctorClass() {}
