#pragma once

#include <QObject>
#include <QObjectComputedProperty>
#include <QQmlEngine>


/*[[[cog
import cog
from MidiRouterChainPrivate import classMidiRouterChainPrivate


cog.outl(classMidiRouterChainPrivate.getClassHeader(),
        dedent=True, trimblanklines=True)

]]] */
class MidiRouterChainPrivate : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged )
    Q_PROPERTY(bool isEasyConfig READ isEasyConfig WRITE setIsEasyConfig NOTIFY isEasyConfigChanged )
    
    QML_ELEMENT
public:
    MidiRouterChainPrivate(QObject *parent = nullptr);
    virtual ~MidiRouterChainPrivate() = default;

    
    
    QString name() const{return m_name;} 
    
void setName(const QString &newName)
    {
        if (m_name == newName)
            return;
        m_name = newName;
        emit nameChanged();
    }


    
    bool isEasyConfig() const{return m_isEasyConfig;} 
    
void setIsEasyConfig(const bool newIsEasyConfig)
    {
        if (m_isEasyConfig == newIsEasyConfig)
            return;
        m_isEasyConfig = newIsEasyConfig;
        emit isEasyConfigChanged();
    }



signals:
    void nameChanged();
    void isEasyConfigChanged();
    

protected:
    

private:
    QString m_name;
    bool m_isEasyConfig;
    
    void ctorClass();
};

//[[[end]]]
