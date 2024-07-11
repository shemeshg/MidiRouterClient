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

void UserDataConfig::clearDropdownlists()
{
    for (const QList<Dropdownlist *> &innerList : m_dropdownlists) {
        for (Dropdownlist *item : innerList) {
            delete item;
        }
    }
    // Clear the outer list
    m_dropdownlists.clear();
}

UserDataConfig::UserDataConfig(QObject *parent)
    : UserDataConfigPrivate{parent}
{
    setActivePresetID(0);
    loadComputerUuid();

    clearDropdownlists();
    Dropdownlist *d = new Dropdownlist();
    d->setData("my data1");
    d->setName("my name1");

    QList<Dropdownlist *> l;
    l.push_back(d);
    d = new Dropdownlist();
    d->setData("my data2");
    d->setName("my name2");
    l.push_back(d);

    m_dropdownlists.push_back(l);
}
