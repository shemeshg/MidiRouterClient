#pragma once
#include <QObject>


class QuitHelper : public QObject {
    Q_OBJECT
public:
    std::function<void()> onApplyFinished = []() {};
public slots:
    void quit();
};