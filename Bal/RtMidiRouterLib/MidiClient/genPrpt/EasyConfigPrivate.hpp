//-define-file header genPrpt/EasyConfigPrivate.h
//-only-file header //-
#pragma once

#include <QObject>
#include <QObjectComputedProperty>
#include <QQmlEngine>
//- #include "../GenHpp/EasyConfigRoute.h"

//-only-file null
#include "../hpp/EasyConfigRoute.hpp"
/*[[[cog
import cog
from EasyConfigPrivate import prptClass


cog.outl(prptClass.getClassHeader(),
        dedent=True, trimblanklines=True)

]]] */
//-only-file header
class EasyConfigPrivate : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<int> keyboardSplits READ keyboardSplits  NOTIFY keyboardSplitsChanged )
    Q_PROPERTY(QStringList zoneNames READ zoneNames WRITE setZoneNames NOTIFY zoneNamesChanged )
    Q_PROPERTY(QList<EasyConfigRoute *> easyConfigRoutes READ easyConfigRoutes  NOTIFY easyConfigRoutesChanged )
    
    QML_ELEMENT
public:
    
    EasyConfigPrivate(QObject *parent = nullptr):QObject(parent){}

    virtual ~EasyConfigPrivate() {
        clearList<EasyConfigRoute *>();
    
    }

    
    
    QList<int> keyboardSplits() const{return m_keyboardSplits;} 
    

    
    QStringList zoneNames() const{return m_zoneNames;} 
    
void setZoneNames(const QStringList &newZoneNames)
    {
        if (m_zoneNames == newZoneNames)
            return;
        m_zoneNames = newZoneNames;
        emit zoneNamesChanged();
    }


    
    QList<EasyConfigRoute *> easyConfigRoutes() const{return m_easyConfigRoutes;} 
    

    
    
        template<typename T = EasyConfigRoute *>
        std::enable_if_t<std::is_same_v<T, EasyConfigRoute *>, void>
        delListItem(int id){
            if (id < m_easyConfigRoutes.size())
            {
                delete m_easyConfigRoutes.at(id);
                m_easyConfigRoutes.removeAt(id);
                emit easyConfigRoutesChanged();
            }
        }

        void addListItem(EasyConfigRoute * item)
        {
            m_easyConfigRoutes.push_back(item);
            emit easyConfigRoutesChanged();
        }

        template<typename T = EasyConfigRoute * >
        std::enable_if_t<std::is_same_v<T, EasyConfigRoute * >, void>
        clearList(){
            qDeleteAll(m_easyConfigRoutes);
            m_easyConfigRoutes.clear();
            emit easyConfigRoutesChanged();
        }

        template<typename T = EasyConfigRoute *>
        std::enable_if_t<std::is_same_v<T, EasyConfigRoute *>, const QList<EasyConfigRoute *>>
        listItems(){
            return m_easyConfigRoutes;
        }

        
    
signals:
    void keyboardSplitsChanged();
    void zoneNamesChanged();
    void easyConfigRoutesChanged();
    

protected:
    QList<int> m_keyboardSplits ;
    QList<EasyConfigRoute *> m_easyConfigRoutes ;
    

private:
    QStringList m_zoneNames ;
    
};
//-only-file null

//[[[end]]]
