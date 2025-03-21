//-define-file header genPrpt/MidiRouteInputCc14bit.h
//-only-file header //-
#pragma once

#include <QObject>
#include <QObjectComputedProperty>
#include <QQmlEngine>
//-only-file header 
//-only-file null

/*[[[cog
import cog
from MidiRouteInputCc14bit import prptClass


cog.outl(prptClass.getClassHeader(),
        dedent=True, trimblanklines=True)

]]] */
//-only-file header
class MidiRouteInputCc14bit : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int channel READ channel WRITE setChannel NOTIFY channelChanged )
    Q_PROPERTY(int cc READ cc WRITE setCc NOTIFY ccChanged )
    
    QML_ELEMENT
public:
    
    MidiRouteInputCc14bit(QObject *parent):QObject(parent){}

    virtual ~MidiRouteInputCc14bit() {
        
    }

    
    
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
    int m_channel = 0;
    int m_cc = 0;
    
};
//-only-file null

//[[[end]]]
