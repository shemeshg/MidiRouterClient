#include "FilterToConslePrivate.h"

/*[[[cog
import cog
from FilterToConslePrivate import classFilterToConslePrivate


cog.outl(classFilterToConslePrivate.getClassCpp(),
        dedent=True, trimblanklines=True)


]]] */
 FilterToConslePrivate:: FilterToConslePrivate(QObject *parent)
    : MidiRoutersFilter(parent)
{
    ctorClass();
}

//[[[end]]]

void FilterToConslePrivate::ctorClass() {
    setFilterType( FilterType::TO_CONSOLE);
}
