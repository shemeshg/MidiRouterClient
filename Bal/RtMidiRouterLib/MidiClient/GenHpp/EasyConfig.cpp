#line 9 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/EasyConfig.hpp"
#include "EasyConfig.h"
     EasyConfig::EasyConfig(QObject * parent) 
#line 25 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/EasyConfig.hpp"
        : EasyConfigPrivate{parent} {};

    QJsonArray EasyConfig::getComboNoesNamesAndNumber() 
#line 33 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/EasyConfig.hpp"
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

    void EasyConfig::addEasyConfigRoute() 
#line 48 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/EasyConfig.hpp"
    {
        auto itm = new EasyConfigRoute();
        addEasyConfigRoutes(itm);
    }

    void EasyConfig::setKeyboardSplits(const QList<int> &newKeyboardSplits) 
#line 56 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/EasyConfig.hpp"
    {
        if (m_keyboardSplits == newKeyboardSplits)
            return;
        m_keyboardSplits = newKeyboardSplits;
        emit keyboardSplitsChanged();
    }



    void EasyConfig::setSplitNoEmmit(int idx, int pos) 
#line 68 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/EasyConfig.hpp"
    {
        m_keyboardSplits[idx] = pos;
    }

    void EasyConfig::emitKeyboardSplitsChanged() 
#line 75 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/EasyConfig.hpp"
    {
        emit keyboardSplitsChanged();
    }

    void EasyConfig::appendSplit(int defaultPosition) 
#line 82 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/EasyConfig.hpp"
    {
        auto zn = keyboardSplits();
        zn.append(defaultPosition);
        appendZoneName(zn.length());
        setKeyboardSplits(zn);
    }

    void EasyConfig::delSplit(int position) 
#line 92 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/EasyConfig.hpp"
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
#line 111 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/EasyConfig.hpp"
    {
        auto s = zoneNames();
        if (position == 1){
            s.append("Split 0");
        }
        s.append( QString{"Split %1"}.arg(position));
        setZoneNames(s);
    }

    std::string EasyConfig::getPositionName(int n) 
#line 123 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/EasyConfig.hpp"
    {
        std::vector<std::string> notes = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
        int inputVal = n;
        std::string noteName = notes[inputVal % 12];
        int octave = std::floor(inputVal / 12.0) - 1;
        return std::to_string(octave) + " " + noteName;
    }
