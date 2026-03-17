#include "quithelper.h"
#include <QCoreApplication>

void QuitHelper::quit() {
    onApplyFinished();
    QCoreApplication::quit();
}

