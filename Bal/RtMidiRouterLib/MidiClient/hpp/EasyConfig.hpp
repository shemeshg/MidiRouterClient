//-define-file body GenHpp/EasyConfig.cpp
//-define-file header GenHpp/EasyConfig.h
//-only-file header //-
#pragma once
#include <QJsonArray>
#include <QJsonObject>
//-only-file body //-
//- #include "EasyConfig.h"
//- {include-header}
#include "../genPrpt/EasyConfigPrivate.hpp" //- #include "../genPrpt/EasyConfigPrivate.h"

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

    //- {fn}
    QJsonArray getComboNoesNamesAndNumber()
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

    //- {fn}
    void delEasyConfigRoute(int idx)
    //-only-file body
    {

        delListItem<EasyConfigRoute *>(idx);
    }

    //- {fn}
    void addEasyConfigRoute()
    //-only-file body
    {
        auto itm = new EasyConfigRoute();
        addListItem(itm);
    }

    //- {fn}
    void setKeyboardSplits(const QList<int> &newKeyboardSplits)
    //-only-file body
    {
        if (m_keyboardSplits == newKeyboardSplits)
            return;
        m_keyboardSplits = newKeyboardSplits;
        emit keyboardSplitsChanged();
    }



    //- {fn}
    void setSplitNoEmmit(int idx, int pos)
    //-only-file body
    {
        m_keyboardSplits[idx] = pos;
    }

    //- {fn}
    void emitKeyboardSplitsChanged()
    //-only-file body
    {
        emit keyboardSplitsChanged();
    }

    //- {fn}
    void appendSplit(int defaultPosition)
    //-only-file body
    {
        auto zn = keyboardSplits();
        zn.append(defaultPosition);
        appendZoneName(zn.length());
        setKeyboardSplits(zn);
    }

    //- {fn}
    void delSplit(int position)
    //-only-file body
    {
        auto ks = keyboardSplits();
        auto kn = zoneNames();
        if (ks.size() == 1){
            ks.clear();
            kn.clear();
        } else {
            ks.removeAt(position);
            kn.removeAt(position + 1);
        }
        setKeyboardSplits(ks);
        setZoneNames(kn);
    }

    //-only-file header
private:
    //- {fn}
    void appendZoneName(int position)
    //-only-file body
    {
        auto s = zoneNames();
        if (position == 1){
            s.append("Split 0");
        }
        s.append( QString{"Split %1"}.arg(position));
        setZoneNames(s);
    }

    //- {fn}
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
