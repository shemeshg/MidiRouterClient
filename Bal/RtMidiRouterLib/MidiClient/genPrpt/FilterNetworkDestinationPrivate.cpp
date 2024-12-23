#include "FilterNetworkDestinationPrivate.h"

/*[[[cog
import cog
from FilterNetworkDestinationPrivate import prptClass


cog.outl(prptClass.getClassCpp(),
        dedent=True, trimblanklines=True)


]]] */
 FilterNetworkDestinationPrivate:: FilterNetworkDestinationPrivate(QObject *parent)
    : MidiRoutersFilter(parent)
{
    ctorClass();
}

//[[[end]]]

void FilterNetworkDestinationPrivate::ctorClass() {
    setFilterType( FilterType::TO_NETWORK);
}
