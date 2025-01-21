//-define-file body GenHpp/EasyConfig.cpp
//-define-file header GenHpp/EasyConfig.h
//-only-file header //-
#pragma once
#include <QJsonArray>
#include <QJsonObject>
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

    //- {function} 0 1
    QJsonArray getComboNoesNamesandNumber()
    //-only-file body
    {
        QJsonArray ret;
        for (int i = 0; i <= 127; ++i) {
            QJsonObject obj;
            obj["text"] = QString{"%1 - %2"}.arg(i).arg(QString::fromStdString(getPositionName(i)));
            obj["value"] = QString::number(i);
            ret.append(obj);
        }

        return ret;
    }
    //-only-file header

    //- {function} 0 1
    void appendSplit()
    //-only-file body
    {
        qDebug()<<"Appended splt and split names";
    }

    //- {function} 0 1
    void delSplit(int position)
    //-only-file body
    {
        qDebug()<<"remove split at position "<<position;
        qDebug()<<"remove split name "<<position;
        // if liast splut do truncate since 2 items to delete
    }

    //-only-file header
private:
    //- {function} 0 1
    std::string getPositionName(int n)
    //-only-file body
    {
        std::vector<std::string> notes = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
        int inputVal = n;
        std::string noteName = notes[inputVal % 12];
        int octave = std::floor(inputVal / 12.0) - 1;
        return std::to_string(octave) + " " + noteName;
    }
    //-only-file header
};
