//-define-file header genPrpt/FilterSwitchData1Data2Private.h
//-only-file header //-

#pragma once

#include <QObject>
#include <QObjectComputedProperty>
#include <QQmlEngine>

//- {include-header}
#include "MidiRoutersFilter.hpp" //- #include "MidiRoutersFilter.h"

//-only-file null
/*[[[cog
import cog
from FilterSwitchData1Data2Private import prptClass


cog.outl(prptClass.getClassHeader(),
        dedent=True, trimblanklines=True)

]]] */
//-only-file header
class FilterSwitchData1Data2Private : public MidiRoutersFilter
{
    Q_OBJECT
    
    QML_ELEMENT
public:
    
    FilterSwitchData1Data2Private(QObject *parent):MidiRoutersFilter(parent){}

    virtual ~FilterSwitchData1Data2Private() {
        
    }

    
    
    
    
signals:
    

protected:
    

private:
    
};
//-only-file null

//[[[end]]]
