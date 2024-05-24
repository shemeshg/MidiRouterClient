#pragma once

#include <QObject>
#include <QObjectComputedProperty>
#include <QQmlEngine>
#include "JsAsync.h"


/*[[[cog
import cog
from BalDataPrivate import classBalDataPrivate


cog.outl(classBalDataPrivate.getClassHeader(),
        dedent=True, trimblanklines=True)

]]] */
class BalDataPrivate : public JsAsync
{
    Q_OBJECT
    Q_PROPERTY(int x READ x WRITE setX NOTIFY xChanged )
    Q_PROPERTY(int y READ y WRITE setY NOTIFY yChanged )
    Q_PROPERTY(int width READ width WRITE setWidth NOTIFY widthChanged )
    Q_PROPERTY(int height READ height WRITE setHeight NOTIFY heightChanged )
    Q_PROPERTY(int serverPort READ serverPort  NOTIFY serverPortChanged )
    Q_PROPERTY(bool isServerRunning READ isServerRunning  NOTIFY isServerRunningChanged )
    
    QML_ELEMENT
public:
    BalDataPrivate(QObject *parent = nullptr);

    
    
    int x() const{return m_x;} 
    
void setX(const int newX)
    {
        if (m_x == newX)
            return;
        m_x = newX;
        emit xChanged();
    }


    
    int y() const{return m_y;} 
    
void setY(const int newY)
    {
        if (m_y == newY)
            return;
        m_y = newY;
        emit yChanged();
    }


    
    int width() const{return m_width;} 
    
void setWidth(const int newWidth)
    {
        if (m_width == newWidth)
            return;
        m_width = newWidth;
        emit widthChanged();
    }


    
    int height() const{return m_height;} 
    
void setHeight(const int newHeight)
    {
        if (m_height == newHeight)
            return;
        m_height = newHeight;
        emit heightChanged();
    }


    
    int serverPort() const{return m_serverPort;} 
    

    
    bool isServerRunning() const{return m_isServerRunning;} 
    


signals:
    void xChanged();
    void yChanged();
    void widthChanged();
    void heightChanged();
    void serverPortChanged();
    void isServerRunningChanged();
    

protected:
    int m_serverPort;
    bool m_isServerRunning;
    

private:
    int m_x;
    int m_y;
    int m_width;
    int m_height;
    
    void ctorClass();
};

//[[[end]]]


