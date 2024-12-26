#pragma once

#include <QObject>
#include <QObjectComputedProperty>
#include <QQmlEngine>

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
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged )
    Q_PROPERTY(QString data READ data WRITE setData NOTIFY dataChanged )
    
    QML_ELEMENT
public:
        Dropdownlist(QObject *parent = nullptr);

    virtual ~Dropdownlist() {
        
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
    void nameChanged();
    void dataChanged();
    

protected:
    

private:
    void ctorClass(); 
QString m_name;
    QString m_data;
    
};
//-only-file null

//[[[end]]]
