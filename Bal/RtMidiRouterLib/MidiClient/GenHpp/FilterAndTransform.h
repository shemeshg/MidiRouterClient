#pragma once
#include "../genPrpt/FilterAndTransformPrivate.h"


class FilterAndTransform : public FilterAndTransformPrivate

{
    Q_OBJECT

    QML_ELEMENT
public:
#line 22 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/FilterAndTransform.hpp"
    explicit FilterAndTransform(QObject *parent = nullptr);
public slots:
#line 32 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/FilterAndTransform.hpp"
    void setFilter(QString name, ConditionAction conditionAction, QString filterChannel,
                  QString filterEvents, QString filterData1, QString filterData2);
private:

};
