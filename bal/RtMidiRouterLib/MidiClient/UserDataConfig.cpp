#include "UserDataConfig.h"
#include <QSettings>
#include <QUuid>

void UserDataConfig::loadComputerUuid()
{
    QSettings settings;
    QString s = settings.value("computerUuid", "").toString();
    if (s.isEmpty()) {
        s = QUuid::createUuid().toString().replace("{", "").replace("}", "");
        settings.setValue("computerUuid", s);
    }
    m_computerUuid = s;
}

UserDataConfig::UserDataConfig(QObject *parent)
    : UserDataConfigPrivate{parent}
{
    setActivePresetID(0);
    loadComputerUuid();
}
