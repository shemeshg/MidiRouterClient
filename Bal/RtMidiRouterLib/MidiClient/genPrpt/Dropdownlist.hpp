//-define-file header genPrpt/Dropdownlist.h
//-only-file header //-
#pragma once

#include <QObject>
#include <QObjectComputedProperty>
#include <QQmlEngine>

//-only-file null
/*[[[cog
import cog
from Dropdownlist import prptClass


cog.outl(prptClass.getClassHeader(),
        dedent=True, trimblanklines=True)

]]] */
//-only-file header
class Dropdownlist : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString uuid READ uuid WRITE setUuid NOTIFY uuidChanged )
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged )
    Q_PROPERTY(QString data READ data WRITE setData NOTIFY dataChanged )
    
    QML_ELEMENT
public:
    
    Dropdownlist(QObject *parent):QObject(parent){}

    virtual ~Dropdownlist() {
        
    }

    
    
    QString uuid() const{return m_uuid;} 
    
void setUuid(const QString &newUuid)
    {
        if (m_uuid == newUuid)
            return;
        m_uuid = newUuid;
        emit uuidChanged();
    }


    
    QString name() const{return m_name;} 
    
void setName(const QString &newName)
    {
        if (m_name == newName)
            return;
        m_name = newName;
        emit nameChanged();
    }


    
    QString data() const{return m_data;} 
    
void setData(const QString &newData)
    {
        if (m_data == newData)
            return;
        m_data = newData;
        emit dataChanged();
    }


    
    
    
signals:
    void uuidChanged();
    void nameChanged();
    void dataChanged();
    

protected:
    

private:
    QString m_uuid ;
    QString m_name ;
    QString m_data ;
    
};
//-only-file null

//[[[end]]]
