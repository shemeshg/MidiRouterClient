//-define-file body GenHpp/EasyConfig.cpp
//-define-file header GenHpp/EasyConfig.h
//-only-file header //-
#pragma once
//- #include "../genPrpt/EasyConfigPrivate.h"
//-only-file body //-
//- #include "EasyConfig.h"
//-only-file null
#include "../genPrpt/EasyConfigPrivate.hpp"
//-only-file header


//-var {PRE} "EasyConfig::"
class EasyConfig : public EasyConfigPrivate

{
    Q_OBJECT
    QML_ELEMENT
public:
    //- {function} 1 1
    explicit EasyConfig(QObject *parent = nullptr)
        //-only-file body
        : EasyConfigPrivate{parent} {};

    //-only-file header
public slots:

private:
};
