//-define-file body GenHpp/UserControl.cpp
//-define-file header GenHpp/UserControl.h
//-only-file header //-
#pragma once
//- #include "../genPrpt/UserControlPrivate.h"
//- #include "MidiClientUtil.h"
//-only-file body //-
//- #include "UserControl.h"
//-only-file null
#include "MidiClientUtil.hpp"
#include "../genPrpt/UserControlPrivate.hpp"
//-only-file header


//-var {PRE} "UserControl::"
class UserControl : public UserControlPrivate
{
    Q_OBJECT
    QML_ELEMENT
public:
    //- {function} 1 1
    explicit UserControl(QObject *parent = nullptr)
    //-only-file body
    : UserControlPrivate{parent}
    {
        setUuid(getUuId());
    };

     //-only-file header
public slots:

private:
};
