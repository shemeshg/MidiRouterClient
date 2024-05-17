// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick
import MidiRouterClient
import QtQuick.Layouts
import Core
import QtQuick.Controls

Window {
    width: Constants.width
    height: Constants.height

    visible: true
    title: "Midi Router"
    color: CoreSystemPalette.window

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: Constants.font.pixelSize

        FormGroupBox {
            title: "Login"
            body: RowLayout {
                CoreButton {
                    text: "ABC"
                }
            }
        }

        FormGroupBox {
            title: qsTr("Server")
            body: RowLayout {
                    CoreButton {
                        text: "shalom"
                    }
                    CoreButton {
                        text: "Olam"
                    }
            }
        }

        Item {
            Layout.fillHeight: true
        }
    }

}

