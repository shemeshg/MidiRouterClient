#include "FilterSchedulePrivate.h"

/*[[[cog
import cog
from FilterSchedulePrivate import prptClass


cog.outl(prptClass.getClassCpp(),
        dedent=True, trimblanklines=True)


]]] */
 FilterSchedulePrivate:: FilterSchedulePrivate(QObject *parent)
    : MidiRoutersFilter(parent)
{
    ctorClass();
}

//[[[end]]]

void FilterSchedulePrivate::ctorClass() {
    setFilterType( FilterType::SCHEDULE_TO);
}
