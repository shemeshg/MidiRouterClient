// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick
import QtQuick.Controls
import Design
import Core
import QtQuick.Layouts


Window {
    width: Constants.balData.width
    height: Constants.balData.height
    x: Constants.balData.x
    y: Constants.balData.y

    visible: true
    title: "Midi Router"
    color: CoreSystemPalette.window

    property bool isClientConnected : {
        return Constants.balData.midiClientConnection.serverStatus
                === Constants.ServerStatus.RUNNING;
    }

    property bool isSubForm: false
    property bool isEasyConfigForm: false
    property string aboutPreviousStr: "InPorts"

    onIsClientConnectedChanged: ()=>{
                                        headerBarId.selectDefaultItem(isClientConnected)
                                }

    Component.onCompleted: {
        CoreSystemPalette.font = Constants.font
        Constants.balData.onApplicationStarted()
        if (Constants.balData.midiClientConnection.userDataConfig.criticalErrorMsg){
            loaderId.sourceComponent = aboutId
            headerBarId.state = "About"
            isSubForm = true
        }
    }

    Component.onDestruction: {
        Constants.balData.saveWidth(width)
        Constants.balData.saveHeight(height)
        Constants.balData.saveX(x)
        Constants.balData.saveY(y)
    }
    ColumnLayout {

        width: parent.width
        height: parent.height

        CoreLabel {
            visible: Constants.balData.midiClientConnection.userDataConfig.criticalErrorMsg
            text: "<h1>" +
                  Constants.balData.midiClientConnection.userDataConfig.criticalErrorMsg +
                  "</h1>"
            color: "darkorange"
        }

        HeaderBar {
            id: headerBarId
            visible: isClientConnected && !isSubForm
        }

        Loader  {
            id: loaderId
            Layout.fillWidth: true
            Layout.fillHeight: true
            sourceComponent: loginId


        }

        Component {
            id: loginId

            Login{

            }
        }

        Component {
            id: virtualPortsId
            VirtualPorts {

            }
        }

        Component {
            id: presetsId
            Presets {
            }
        }

        Component {
            id: userControlsId
            UserControls {                 
            }
        }


        Component {
            id: inPortsId
            InPorts {
            }
        }

        Component {
            id: aboutId
            About {}

        }

        Item {
            Layout.fillHeight: true
        }

        RowLayout {
            visible:  headerBarId.state === "InPorts" && isSubForm && isEasyConfigForm

            Item {
                Layout.fillWidth: true
            }
            GroupBox {
                RowLayout {
                    CoreButton {
                        id: easyConfigRoutesId
                        text: "Routes"
                        hooverText: "Routes"
                        autoExclusive: true
                        checkable: true
                        checked: true
                        isAnimation: false
                    }
                    CoreButton {
                        id: easyConfigSplitsId
                        text: "Splits"
                        hooverText: "Keyboard Splits"
                        autoExclusive: true
                        checkable: true
                        checked: false
                        isAnimation: false
                    }
                }
            }
            Item {
                Layout.fillWidth: true
            }
        }

        RowLayout {
            visible:  headerBarId.state === "UserControls" && !isSubForm
            Item {
                Layout.fillWidth: true
            }
            GroupBox {
                RowLayout {
                    CoreButton {
                        id: editControlsId
                        text: "Controls"
                        hooverText: "User controls"
                        autoExclusive: true
                        checkable: true
                        checked: true
                        onClicked: {                            
                            loaderId.item.setLoaderToControls()
                        }
                        isAnimation: false
                    }
                    CoreButton {
                        id: editDropdownsId
                        text: "Dropdowns"
                        hooverText: "Map CC/Program number to meaningfull name"
                        autoExclusive: true
                        checkable: true
                        checked: false
                        onClicked: {
                            state = "Dropdowns"
                            loaderId.item.setLoaderToDropdowns()
                        }
                        isAnimation: false
                    }
                }
            }
            Item {
                Layout.fillWidth: true
            }
        }

        GroupBox {
            Layout.margins:  Constants.font.pixelSize

            Layout.fillWidth: true
            visible: headerBarId.state !== "About"
            RowLayout {
                anchors.left: parent.left
                anchors.right: parent.right
                CoreButton {
                    text: "Apply"
                    visible: Constants.balData.midiClientConnection.serverStatus
                             === Constants.ServerStatus.RUNNING
                    onClicked: {
                        Constants.balData.applyConfig(() => {
                        });
                    }
                }

                CoreLabel {
                    text: Constants.balData.midiClientConnection.userDataConfig.activePreset.name
                }

                Item {
                    Layout.fillWidth: true
                }

                CoreButton {
                    text: "⋮"
                    hooverText: "About and settings"
                    onClicked: {
                        if (headerBarId.state === "About" ){
                            headerBarId.state = aboutPreviousStr
                            isSubForm = false
                        } else {
                            aboutPreviousStr = headerBarId.state
                            loaderId.sourceComponent = aboutId
                            headerBarId.state = "About"
                            isSubForm = true
                        }
                    }
                }
            }
        }

        states: [
            State {
                name: "Login"
                when: headerBarId.state === "Login"
                StateChangeScript {
                          script:
                          {
                              loaderId.sourceComponent = loginId
                              isSubForm = false
                              if (isClientConnected){
                                  Constants.balData.saveDefaultHeaderTabSelected("Login");
                              }
                          }
                 }
            },
            State {
                name: "VirtualPorts"
                when: headerBarId.state === "VirtualPorts"
                StateChangeScript {
                          script: {
                              loaderId.sourceComponent = virtualPortsId
                              Constants.balData.saveDefaultHeaderTabSelected("VirtualPorts");
                          }
                 }
            },
            State {
                name: "Presets"
                when: headerBarId.state === "Presets"
                StateChangeScript {
                          script: {
                              loaderId.sourceComponent = presetsId
                              isSubForm = false
                              Constants.balData.saveDefaultHeaderTabSelected("Presets");
                          }
                 }
            }
            ,
            State {
                name: "UserControls"
                when: headerBarId.state === "UserControls"
                StateChangeScript {
                          script: {
                              loaderId.sourceComponent = userControlsId
                              isSubForm = false
                              Constants.balData.saveDefaultHeaderTabSelected("UserControls");
                          }
                 }
            },
            State {
                name: "InPorts"
                when: headerBarId.state === "InPorts"
                StateChangeScript {
                          script: {
                              loaderId.sourceComponent = inPortsId
                              isSubForm = false
                              Constants.balData.saveDefaultHeaderTabSelected("InPorts");
                          }
                 }
            }
        ]
    }
}


