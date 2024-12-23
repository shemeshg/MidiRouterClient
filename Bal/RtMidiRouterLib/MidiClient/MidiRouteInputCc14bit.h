#pragma once

#include <QObject>
#include <QObjectComputedProperty>
#include <QQmlEngine>

/*[[[cog
import cog
from MidiRouteInputCc14bit import classMidiRouteInputCc14bit


cog.outl(classMidiRouteInputCc14bit.getClassHeader(),
        dedent=True, trimblanklines=True)

]]] */
class MidiRouteInputCc14bit : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int channel READ channel WRITE setChannel NOTIFY channelChanged )
    Q_PROPERTY(int cc READ cc WRITE setCc NOTIFY ccChanged )
    
    QML_ELEMENT
public:
    MidiRouteInputCc14bit(QObject *parent = nullptr);
    virtual ~MidiRouteInputCc14bit() = default;

    
    
    int channel() const{return m_channel;} 
    
void setChannel(const int newChannel)
    {
        if (m_channel == newChannel)
            return;
        m_channel = newChannel;
        emit channelChanged();
    }


    
    int cc() const{return m_cc;} 
    
void setCc(const int newCc)
    {
        if (m_cc == newCc)
            return;
        m_cc = newCc;
        emit ccChanged();
    }


    
    
signals:
    void channelChanged();
    void ccChanged();
    

protected:
    

private:
    int m_channel;
    int m_cc;
    
    void ctorClass();
};

//[[[end]]]
