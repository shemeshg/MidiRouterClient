#pragma once


#include "MidiRoutersFilter.h"
#include <QObject>
#include <QObjectComputedProperty>
#include <QQmlEngine>

/*[[[cog
import cog
from FilterAndTransformPrivate import prptClass


cog.outl(prptClass.getClassHeader(),
        dedent=True, trimblanklines=True)

]]] */
class FilterAndTransformPrivate : public MidiRoutersFilter
{
    Q_OBJECT
    Q_PROPERTY(ConditionAction conditionAction READ conditionAction WRITE setConditionAction NOTIFY conditionActionChanged )
    Q_PROPERTY(QString filterChannel READ filterChannel WRITE setFilterChannel NOTIFY filterChannelChanged )
    Q_PROPERTY(QString filterEvents READ filterEvents WRITE setFilterEvents NOTIFY filterEventsChanged )
    Q_PROPERTY(QString filterData1 READ filterData1 WRITE setFilterData1 NOTIFY filterData1Changed )
    Q_PROPERTY(QString filterData2 READ filterData2 WRITE setFilterData2 NOTIFY filterData2Changed )
    
    QML_ELEMENT
public:
    FilterAndTransformPrivate(QObject *parent = nullptr);
    virtual ~FilterAndTransformPrivate() {
        
    }

    
enum class ConditionAction {
        DO_NOT_DELETE, DELETE_IF_NOT_MET_CONDITION, DELETE_IF_MET_CONDITION
    };
Q_ENUM(ConditionAction)

    
    ConditionAction conditionAction() const{return m_conditionAction;} 
    
void setConditionAction(const ConditionAction &newConditionAction)
    {
        if (m_conditionAction == newConditionAction)
            return;
        m_conditionAction = newConditionAction;
        emit conditionActionChanged();
    }


    
    QString filterChannel() const{return m_filterChannel;} 
    
void setFilterChannel(const QString &newFilterChannel)
    {
        if (m_filterChannel == newFilterChannel)
            return;
        m_filterChannel = newFilterChannel;
        emit filterChannelChanged();
    }


    
    QString filterEvents() const{return m_filterEvents;} 
    
void setFilterEvents(const QString &newFilterEvents)
    {
        if (m_filterEvents == newFilterEvents)
            return;
        m_filterEvents = newFilterEvents;
        emit filterEventsChanged();
    }


    
    QString filterData1() const{return m_filterData1;} 
    
void setFilterData1(const QString &newFilterData1)
    {
        if (m_filterData1 == newFilterData1)
            return;
        m_filterData1 = newFilterData1;
        emit filterData1Changed();
    }


    
    QString filterData2() const{return m_filterData2;} 
    
void setFilterData2(const QString &newFilterData2)
    {
        if (m_filterData2 == newFilterData2)
            return;
        m_filterData2 = newFilterData2;
        emit filterData2Changed();
    }


    
    
signals:
    void conditionActionChanged();
    void filterChannelChanged();
    void filterEventsChanged();
    void filterData1Changed();
    void filterData2Changed();
    

protected:
    

private:
    ConditionAction m_conditionAction;
    QString m_filterChannel;
    QString m_filterEvents;
    QString m_filterData1;
    QString m_filterData2;
    
    void ctorClass();
};

//[[[end]]]
