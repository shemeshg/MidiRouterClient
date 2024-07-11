#pragma once

#include <QObject>
#include <QObjectComputedProperty>
#include <QQmlEngine>

/*[[[cog
import cog
from UserDataConfigPrivate import classUserDataConfigPrivate


cog.outl(classUserDataConfigPrivate.getClassHeader(),
        dedent=True, trimblanklines=True)

]]] */
class UserDataConfigPrivate : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int activePresetID READ activePresetID WRITE setActivePresetID NOTIFY activePresetIDChanged )
    Q_PROPERTY(QString computerUuid READ computerUuid  CONSTANT )
    
    QML_ELEMENT
public:
    UserDataConfigPrivate(QObject *parent = nullptr);

    
    
    int activePresetID() const{return m_activePresetID;} 
    
void setActivePresetID(const int newActivePresetID)
    {
        if (m_activePresetID == newActivePresetID)
            return;
        m_activePresetID = newActivePresetID;
        emit activePresetIDChanged();
    }


    
    QString computerUuid() const{return m_computerUuid;} 
    


signals:
    void activePresetIDChanged();
    

protected:
    QString m_computerUuid;
    

private:
    int m_activePresetID;
    
    void ctorClass();
};

//[[[end]]]
