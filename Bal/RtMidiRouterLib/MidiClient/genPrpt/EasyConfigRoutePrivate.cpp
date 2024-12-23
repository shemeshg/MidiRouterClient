#include "EasyConfigRoutePrivate.h"

/*[[[cog
import cog
from EasyConfigRoutePrivate import prptClass


cog.outl(prptClass.getClassCpp(),
        dedent=True, trimblanklines=True)


]]] */
 EasyConfigRoutePrivate:: EasyConfigRoutePrivate(QObject *parent)
    : QObject(parent)
{
    ctorClass();
}

//[[[end]]]

void EasyConfigRoutePrivate::ctorClass() {
    setSplitRangeId(-1);
    setFromSelectedMidiEventTypeId(0);
    setFromChannel(-1);
    setFromData1(-1);
    setTranspose(0);

    setFromCcOrNrpnStart(0);
    setFromCcOrNrpnEnd(127);
    setToCcOrNrpnStart(0);
    setToCcOrNrpnEnd(127);

    setToSelectedMidiEventTypeId(0);
    setToChannel(-1);
    setToData1(-1);

    setToDestinationName("");

}
