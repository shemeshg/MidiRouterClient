#pragma once
#include "../genPrpt/FilterAndTransformPrivate.h"


class FilterAndTransform : public FilterAndTransformPrivate

{
    Q_OBJECT

    QML_ELEMENT
public:
    explicit FilterAndTransform(QObject *parent = nullptr);
public slots:
    void setFilter(QString name, ConditionAction conditionAction, QString filterChannel,
                  QString filterEvents, QString filterData1, QString filterData2);
private:

};
