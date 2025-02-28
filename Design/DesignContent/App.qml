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


