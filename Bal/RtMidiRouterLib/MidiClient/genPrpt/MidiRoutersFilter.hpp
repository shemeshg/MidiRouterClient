//-define-file header genPrpt/MidiRoutersFilter.h
//-only-file header //-
#pragma once

#include <QObject>
#include <QObjectComputedProperty>
#include <QQmlEngine>
//-only-file header 

//-only-file null

/*[[[cog
import cog
from MidiRoutersFilter import prptClass


cog.outl(prptClass.getClassHeader(),
        dedent=True, trimblanklines=True)

]]] */
//-only-file header
class MidiRoutersFilter : public QObject
{
    Q_OBJECT
    Q_PROPERTY(FilterType filterType READ filterType WRITE setFilterType NOTIFY filterTypeChanged )
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged )
    
    QML_ELEMENT
public:
    
    MidiRoutersFilter(QObject *parent = nullptr):QObject(parent){}

    virtual ~MidiRoutersFilter() {
        
    }

    
enum class FilterType {
        TO_MIDI_DESTINATION, TO_CONSOLE, TO_NETWORK, SCHEDULE_TO, FILTER_AND_TRANSFORM
    };
Q_ENUM(FilterType)

    
    FilterType filterType() const{return m_filterType;} 
    
void setFilterType(const FilterType &newFilterType)
    {
        if (m_filterType == newFilterType)
            return;
        m_filterType = newFilterType;
        emit filterTypeChanged();
    }


    
    QString name() const{return m_name;} 
    
void setName(const QString &newName)
    {
        if (m_name == newName)
            return;
        m_name = newName;
        emit nameChanged();
    }



    template<typename T>
    void clearList();
    
    template<typename T>
    void delListItem(int id);

    
    
signals:
    void filterTypeChanged();
    void nameChanged();
    

protected:
    

private:
    FilterType m_filterType;
    QString m_name;
    
};
//-only-file null

//[[[end]]]
