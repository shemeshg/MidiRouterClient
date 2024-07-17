#pragma once

#include <QObject>
#include <QObjectComputedProperty>
#include <QQmlEngine>

/*[[[cog
import cog
from MidiRouteInputPrivate import classMidiRouteInputPrivate


cog.outl(classMidiRouteInputPrivate.getClassHeader(),
        dedent=True, trimblanklines=True)

]]] */
class MidiRouteInputPrivate : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged )
    
    QML_ELEMENT
public:
    MidiRouteInputPrivate(QObject *parent = nullptr);
    virtual ~MidiRouteInputPrivate() = default;

    
    
    QString name() const{return m_name;} 
    
void setName(const QString &newName)
    {
        if (m_name == newName)
            return;
        m_name = newName;
        emit nameChanged();
    }



signals:
    void nameChanged();
    

protected:
    

private:
    QString m_name;
    
    void ctorClass();
};

//[[[end]]]
