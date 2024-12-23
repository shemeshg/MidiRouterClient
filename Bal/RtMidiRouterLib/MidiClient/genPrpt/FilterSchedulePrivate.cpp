#include "FilterSchedulePrivate.h"

/*[[[cog
import cog
from FilterSchedulePrivate import classFilterSchedulePrivate


cog.outl(classFilterSchedulePrivate.getClassCpp(),
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
