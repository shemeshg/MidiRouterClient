#include "EasyConfig.h"
     EasyConfig::EasyConfig(QObject * parent) 
        : EasyConfigPrivate{parent} {};

    QJsonArray EasyConfig::getComboNoesNamesandNumber() 
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


    void EasyConfig::setKeyboardSplits(const QList<int> &newKeyboardSplits) 
    {
        if (m_keyboardSplits == newKeyboardSplits)
            return;
        m_keyboardSplits = newKeyboardSplits;
        emit keyboardSplitsChanged();
    }



    void EasyConfig::setSplitNoEmmit(int idx, int pos) 
    {
        m_keyboardSplits[idx] = pos;
    }

    void EasyConfig::emitKeyboardSplitsChanged() 
    {
        emit keyboardSplitsChanged();
    }

    void EasyConfig::appendSplit(int defaultPosition) 
    {
        auto zn = keyboardSplits();
        zn.append(defaultPosition);
        appendZoneName(zn.length());
        setKeyboardSplits(zn);
    }

    void EasyConfig::delSplit(int position) 
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

    void EasyConfig::appendZoneName(int position) 
    {
        auto s = zoneNames();
        if (position == 1){
            s.append("Split 0");
        }
        s.append( QString{"Split %1"}.arg(position));
        setZoneNames(s);
    }

    std::string EasyConfig::getPositionName(int n) 
    {
        std::vector<std::string> notes = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
        int inputVal = n;
        std::string noteName = notes[inputVal % 12];
        int octave = std::floor(inputVal / 12.0) - 1;
        return std::to_string(octave) + " " + noteName;
    }
