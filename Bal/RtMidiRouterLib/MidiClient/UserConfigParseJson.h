#ifndef USERCONFIGPARSEJSON_H
#define USERCONFIGPARSEJSON_H

#include "UserDataConfig.h"
#include <QtCore/qjsonarray.h>
#include <QtCore/qjsondocument.h>
class UserConfigParseJson
{
public:
    UserConfigParseJson(){

    }

    void setChanges(UserDataConfig *userDataConfig, QJsonDocument &jsonDoc){
        updateVirtualInPorts(userDataConfig,jsonDoc["virtualInPorts"]);

        if (jsonDoc["_activePresetID"].isDouble()) {
            userDataConfig->setActivePresetID(jsonDoc["_activePresetID"].toInt());
        }

        updateDropdownlists(userDataConfig, jsonDoc["dropdownlists"]);
    }

private:
    void updateVirtualInPorts(UserDataConfig *userDataConfig, const QJsonValue &virtualInPorts){
        if (virtualInPorts.isArray()){
            auto array = virtualInPorts.toArray();
            userDataConfig->clearVirtualPorts();
            for (const QJsonValue &value : array) {
                userDataConfig->addVirtualPort(value.toString());
            }

        }
    }

    void updateDropdownlists(UserDataConfig *userDataConfig, const QJsonValue &dropdownlists){
        userDataConfig->clearDropdownlists();
         if (dropdownlists.isArray()) {
            auto array = dropdownlists.toArray();
            for (const QJsonValue &value : array) {
                userDataConfig->addDropdownList(value["name"].toString(),value["data"].toString());
            }
         }
    }
};

#endif // USERCONFIGPARSEJSON_H
