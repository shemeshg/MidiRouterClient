

#pragma once
#include "EasyConfigPrivate.h"
#include "EasyConfigRoute.h"

class EasyConfig : public EasyConfigPrivate

{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit EasyConfig(QObject *parent = nullptr)
        : EasyConfigPrivate{parent} {};

    void clearEasyConfigRoute(){
        for (const EasyConfigRoute *item : m_easyConfigRoutes) {
            delete item;
        }
        // Clear the outer list
        m_easyConfigRoutes.clear();
        emit easyConfigRoutesChanged();
    }

    void addEasyConfigRoute(EasyConfigRoute *itm){
        m_easyConfigRoutes.push_back(itm);
        emit easyConfigRoutesChanged();
    }


public slots:

private:
};
