#pragma once
#include <QJsonArray>
#include <QJsonObject>
#include "../genPrpt/EasyConfigPrivate.h"


class EasyConfig : public EasyConfigPrivate

{
    Q_OBJECT
    QML_ELEMENT
public:
#line 23 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/EasyConfig.hpp"
    explicit EasyConfig(QObject *parent = nullptr);
public slots:

#line 31 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/EasyConfig.hpp"
    QJsonArray getComboNoesNamesAndNumber();
#line 46 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/EasyConfig.hpp"
    void addEasyConfigRoute();
#line 54 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/EasyConfig.hpp"
    void setKeyboardSplits(const QList<int> &newKeyboardSplits);
#line 66 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/EasyConfig.hpp"
    void setSplitNoEmmit(int idx, int pos);
#line 73 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/EasyConfig.hpp"
    void emitKeyboardSplitsChanged();
#line 80 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/EasyConfig.hpp"
    void appendSplit(int defaultPosition);
#line 90 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/EasyConfig.hpp"
    void delSplit(int position);
private:
#line 109 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/EasyConfig.hpp"
    void appendZoneName(int position);
#line 121 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/EasyConfig.hpp"
    std::string getPositionName(int n);
};
