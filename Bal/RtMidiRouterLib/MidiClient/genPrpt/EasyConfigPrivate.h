#pragma once

#include <QObject>
#include <QObjectComputedProperty>
#include <QQmlEngine>
#include "../GenHpp/EasyConfigRoute.h"

class EasyConfigPrivate : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<int> keyboardSplits READ keyboardSplits WRITE setKeyboardSplits NOTIFY keyboardSplitsChanged )
    Q_PROPERTY(QStringList zoneNames READ zoneNames WRITE setZoneNames NOTIFY zoneNamesChanged )
    Q_PROPERTY(QList<EasyConfigRoute *> easyConfigRoutes READ easyConfigRoutes  NOTIFY easyConfigRoutesChanged )
    
    QML_ELEMENT
public:
    
    EasyConfigPrivate(QObject *parent = nullptr):QObject(parent){}

    virtual ~EasyConfigPrivate() {
        clearEasyConfigRoutes();
    
    }

    
    
    QList<int> keyboardSplits() const{return m_keyboardSplits;} 
    
void setKeyboardSplits(const QList<int> &newKeyboardSplits)
    {
        if (m_keyboardSplits == newKeyboardSplits)
            return;
        m_keyboardSplits = newKeyboardSplits;
        emit keyboardSplitsChanged();
    }


    
    QStringList zoneNames() const{return m_zoneNames;} 
    
void setZoneNames(const QStringList &newZoneNames)
    {
        if (m_zoneNames == newZoneNames)
            return;
        m_zoneNames = newZoneNames;
        emit zoneNamesChanged();
    }


    
    QList<EasyConfigRoute *> easyConfigRoutes() const{return m_easyConfigRoutes;} 
    

    
        void delEasyConfigRoutes(int id)
        {
            if (id < m_easyConfigRoutes.size())
            {
                delete m_easyConfigRoutes.at(id);
                m_easyConfigRoutes.removeAt(id);
                emit easyConfigRoutesChanged();
            }
        }

        void addEasyConfigRoutes(EasyConfigRoute * item)
        {
            m_easyConfigRoutes.push_back(item);
            emit easyConfigRoutesChanged();
        }

        void clearEasyConfigRoutes()
        {
            for (const EasyConfigRoute * item : m_easyConfigRoutes) {
                delete item;
            }
            // Clear the outer list
            m_easyConfigRoutes.clear();
            emit easyConfigRoutesChanged();
        }
        
    
signals:
    void keyboardSplitsChanged();
    void zoneNamesChanged();
    void easyConfigRoutesChanged();
    

protected:
    QList<EasyConfigRoute *> m_easyConfigRoutes;
    

private:
    QList<int> m_keyboardSplits;
    QStringList m_zoneNames;
    
};
