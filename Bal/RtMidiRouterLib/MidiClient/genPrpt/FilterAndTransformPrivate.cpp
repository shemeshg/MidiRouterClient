#include "FilterAndTransformPrivate.h"

/*[[[cog
import cog
from FilterAndTransformPrivate import prptClass


cog.outl(prptClass.getClassCpp(),
        dedent=True, trimblanklines=True)


]]] */
 FilterAndTransformPrivate:: FilterAndTransformPrivate(QObject *parent)
    : MidiRoutersFilter(parent)
{
    ctorClass();
}

//[[[end]]]

void FilterAndTransformPrivate::ctorClass() {
    setFilterType( FilterType::FILTER_AND_TRANSFORM);
}
