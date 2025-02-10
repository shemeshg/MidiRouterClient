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

//- {fn}
QString getUuId()
//-only-file body
{
    return QUuid::createUuid().toString().replace("{", "").replace("}", "");
}

//- {fn}
template<typename T>
void moveItem(std::vector<T>& vec, int intFrom, int intTo)
//-only-file body
{
    int size = vec.size();
    intTo = (intTo + size) % size;

    if (intFrom < 0 || intFrom >= size || intTo < 0 || intTo >= size) {
        throw std::out_of_range("Index out of range");
    }

    if (intFrom == intTo) {
        return; // No need to move if the positions are the same
    }

    if (intFrom < intTo) {
        std::rotate(vec.begin() + intFrom, vec.begin() + intFrom + 1, vec.begin() + intTo + 1);
    } else {
        std::rotate(vec.begin() + intTo, vec.begin() + intFrom, vec.begin() + intFrom + 1);
    }
}
//-only-file header
