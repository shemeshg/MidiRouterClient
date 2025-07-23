//-define-file body GenHpp/UserControl.cpp
//-define-file header GenHpp/UserControl.h
//-only-file header //-
#pragma once
//- #include "../genPrpt/UserControlPrivate.h"
//- #include "MidiClientUtil.h"
//-only-file body //-
//- #include "UserControl.h"
//-only-file null
#include "MidiClientUtil.hpp"
#include "../genPrpt/UserControlPrivate.hpp"
//-only-file header


//-var {PRE} "UserControl::"
class UserControl : public UserControlPrivate
{
    Q_OBJECT
    QML_ELEMENT
public:
    //- {function} 1 1
    explicit UserControl(QObject *parent)
    //-only-file body
    : UserControlPrivate{parent}
    {
        setUuid(getUuId());
    };

    //- {fn}
    QJsonObject genJson()
    //-only-file body
    {
        QJsonObject userControlObj;
        userControlObj["uuid"] = uuid();
        userControlObj["eventType"] = static_cast<int>(eventType());
        userControlObj["description"] = description();
        userControlObj["inputVal"] = inputVal();
        userControlObj["minVal"] = minVal();
        userControlObj["maxVal"] = maxVal();
        userControlObj["is64Mode"] = is64Mode();
        userControlObj["channelId"] = channelId();
        userControlObj["ccId"] = ccId();
        userControlObj["nrpnControl"] = nrpnControl();
        userControlObj["outputPortnName"] = outputPortnName();
        userControlObj["isShowDropdown"] = isShowDropdown();
        userControlObj["dropdownListUuid"] = dropdownListUuid();
        userControlObj["isSendOnPresetChange"] = isSendOnPresetChange();
        return userControlObj;
    }

     //-only-file header
public slots:

private:
};
