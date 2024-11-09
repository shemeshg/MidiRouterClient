// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick
import Design
import Core
import QtQuick.Layouts
import QtQuick.Controls

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


        HeaderBar {
            id: headerBarId
        }

        Loader {
            id: loaderId
            Layout.fillWidth: true


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
            id: easyConfigId
            EasyConfig {
            }
        }

        Item {
            Layout.fillHeight: true
        }


        states: [
            State {
                name: "Login"
                when: headerBarId.state === "Login"
                PropertyChanges { target: loaderId; sourceComponent: loginId }
            },
            State {
                name: "VirtualPorts"
                when: headerBarId.state === "VirtualPorts"
                PropertyChanges { target: loaderId; sourceComponent: virtualPortsId }
            },
            State {
                name: "Presets"
                when: headerBarId.state === "Presets"
                PropertyChanges { target: loaderId; sourceComponent: presetsId }
            }
            ,
            State {
                name: "UserControls"
                when: headerBarId.state === "UserControls"
                PropertyChanges { target: loaderId; sourceComponent: userControlsId }
            },
            State {
                name: "EasyConfig"
                when: headerBarId.state === "EasyConfig"
                PropertyChanges { target: loaderId; sourceComponent: easyConfigId }
            }
        ]
    }
}


