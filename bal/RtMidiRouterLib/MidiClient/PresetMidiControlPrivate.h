#pragma once

#include <QObject>
#include <QObjectComputedProperty>
#include <QQmlEngine>

/*[[[cog
import cog
from PresetMidiControlPrivate import classPresetMidiControlPrivate


cog.outl(classPresetMidiControlPrivate.getClassHeader(),
        dedent=True, trimblanklines=True)

]]] */
class PresetMidiControlPrivate : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString portName READ portName WRITE setPortName NOTIFY portNameChanged )
    
    QML_ELEMENT
public:
    PresetMidiControlPrivate(QObject *parent = nullptr);
    virtual ~PresetMidiControlPrivate() = default;

    
    
    QString portName() const{return m_portName;} 
    
void setPortName(const QString &newPortName)
    {
        if (m_portName == newPortName)
            return;
        m_portName = newPortName;
        emit portNameChanged();
    }



signals:
    void portNameChanged();
    

protected:
    

private:
    QString m_portName;
    
    void ctorClass();
};

//[[[end]]]
