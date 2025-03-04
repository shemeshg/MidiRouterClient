//-define-file body GenHpp/MidiClientUtil.cpp
//-define-file header GenHpp/MidiClientUtil.h
//-only-file header //-
#pragma once
#include <QString>
#include <QJsonValueRef>
#include <QJsonObject>
#include <QJsonArray>
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


template<typename T = QJsonArray>
std::enable_if_t<std::is_same_v<T, QJsonArray>, QJsonArray>
getJson(QJsonValueRef obj)
{
    if (obj.isArray()){
        return obj.toArray();
    } else {
        throw std::runtime_error("Unexpected JSON format");
    }
}

template<typename T = QJsonObject>
std::enable_if_t<std::is_same_v<T, QJsonObject>, QJsonObject>
getJson(QJsonValueRef obj)
{
    if (obj.isObject()){
        return obj.toObject();
    } else {
        throw std::runtime_error("Unexpected JSON format");
    }
}

template<typename T = QString>
std::enable_if_t<std::is_same_v<T, QString>, QString>
getJson(QJsonValueRef obj)
{
    if(obj.isString()){
        return obj.toString();
    } else {
        throw std::runtime_error("Unexpected JSON format");
    }
}

template<typename T = bool>
std::enable_if_t<std::is_same_v<T, bool>, bool>
getJson(QJsonValueRef obj)
{
    if(obj.isBool()){
        return obj.toBool();
    } else {
        throw std::runtime_error("Unexpected JSON format");
    }
}

template<typename T = double>
std::enable_if_t<std::is_same_v<T, double>, double>
getJson(QJsonValueRef obj)
{
    if(obj.isDouble()){
        return obj.toDouble();
    } else {
        throw std::runtime_error("Unexpected JSON format");
    }
}


template<typename T = int>
std::enable_if_t<std::is_same_v<T, int>, int>
getJson(QJsonValueRef obj)
{
    if(obj.isDouble()){
        return obj.toDouble();
    } else {
        throw std::runtime_error("Unexpected JSON format");
    }
}

//-only-file header
template<typename T>
QList<T>  convertJsonArrayToQList(const QJsonValueRef &j)
{
    QList<T>  stringList;
    for (const auto &value : getJson<QJsonArray>(j)) {
        stringList.append(getJson<T>(value));
    }
    return stringList;
}


