#pragma once
#include "MidiRouterChainPrivate.h"


class MidiRouterChain : public MidiRouterChainPrivate

{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit MidiRouterChain(QObject *parent = nullptr)
        : MidiRouterChainPrivate{parent}{

    };



public slots:

signals:


private:

};
