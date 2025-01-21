#pragma once
#include <QJsonArray>
#include <QJsonObject>
#include "../genPrpt/EasyConfigPrivate.h"


class EasyConfig : public EasyConfigPrivate

{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit EasyConfig(QObject *parent = nullptr);
public slots:

    QJsonArray getComboNoesNamesandNumber();
    void setKeyboardSplits(const QList<int> &newKeyboardSplits);
    void setSplitNoEmmit(int idx, int pos);
    void emitKeyboardSplitsChanged();
    void appendSplit(int defaultPosition);
    void delSplit(int position);
private:
    void appendZoneName(int position);
    std::string getPositionName(int n);
};
