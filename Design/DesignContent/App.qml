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

    onIsClientConnectedChanged: ()=>{
                                        headerBarId.selectDefaultItem(isClientConnected)
                                }

    Component.onCompleted: {
        CoreSystemPalette.font = Constants.font
        Constants.balData.onApplicationStarted()
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
            visible: Constants.balData.midiClientConnection.serverStatus
                     === Constants.ServerStatus.RUNNING
        }

        StackView  {
            id: loaderId
            Layout.fillWidth: true
            initialItem: loginId
            pushEnter: Transition {}
            pushExit: Transition {}
            popEnter: Transition {}
            popExit: Transition {}
            replaceEnter: Transition {}
            replaceExit: Transition {}

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




        Item {
            Layout.fillHeight: true
        }

        RowLayout {
            visible:  headerBarId.state === "UserControls"
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

                            loaderId.currentItem.setLoaderToControls()
                        }
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
                            loaderId.currentItem.setLoaderToDropdowns()
                        }
                    }
                }
            }
            Item {
                Layout.fillWidth: true
            }
        }

        GroupBox {
            visible: Constants.balData.midiClientConnection.serverStatus
                     === Constants.ServerStatus.RUNNING
            Layout.fillWidth: true
            RowLayout {
                anchors.left: parent.left
                anchors.right: parent.right
                CoreButton {
                    text: "Apply"
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


            }
        }

        states: [
            State {
                name: "Login"
                when: headerBarId.state === "Login"
                StateChangeScript {
                          script: loaderId.push(loginId)
                 }
            },
            State {
                name: "VirtualPorts"
                when: headerBarId.state === "VirtualPorts"
                StateChangeScript {
                          script: loaderId.push(virtualPortsId)
                 }
            },
            State {
                name: "Presets"
                when: headerBarId.state === "Presets"
                StateChangeScript {
                          script: loaderId.push(presetsId)
                 }
            }
            ,
            State {
                name: "UserControls"
                when: headerBarId.state === "UserControls"
                StateChangeScript {
                          script: loaderId.push(userControlsId)
                 }
            },
            State {
                name: "InPorts"
                when: headerBarId.state === "InPorts"
                StateChangeScript {
                          script: loaderId.push(inPortsId)
                 }
            }
        ]
    }
}


