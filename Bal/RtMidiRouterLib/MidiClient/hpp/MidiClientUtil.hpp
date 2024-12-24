//-define-file body GenHpp/MidiClientUtil.cpp
//-define-file header GenHpp/MidiClientUtil.h
//-only-file header //-
#pragma once
#include <QString>
//-only-file body //-
//- #include "MidiClientUtil.h"
#include <QUuid>
//-only-file null
//-only-file header
//-var {PRE} ""

//- {function} 0 1
QString getUuId()
//-only-file body
{
    return QUuid::createUuid().toString().replace("{", "").replace("}", "");
}
