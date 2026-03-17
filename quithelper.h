#pragma once
#include <QObject>


class QuitHelper : public QObject {
    Q_OBJECT
public slots:
    void quit();
};