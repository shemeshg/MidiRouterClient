// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only
import QtQuick
import MidiRouterClient
import QtQuick.Layouts
import Core
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
    }

    Component.onDestruction: {
        Constants.balData.saveWidth(width)
        Constants.balData.saveHeight(height)
        Constants.balData.saveX(x)
        Constants.balData.saveY(y)
    }
    ColumnLayout {
        anchors.fill: parent
        anchors.margins: Constants.font.pixelSize

        FormGroupBox {
            title: "<h3>Login</h3>"
            body: ColumnLayout {
                RowLayout {
                    CoreLabel {
                        text: "Server name: "
                    }
                    CoreTextField {
                        Layout.fillWidth: true
                        text: "localhost"
                    }
                }
                RowLayout {
                    CoreLabel {
                        text: "Port: "
                    }
                    CoreTextField {
                        Layout.fillWidth: true
                        text: "12345"
                    }
                    CoreSwitch {
                        text: "local"
                    }
                }
                CoreButton {
                    text: "Connect"
                }
            }
        }

        FormGroupBox {
            title: qsTr("<h3>Server</h3>")
            body: ColumnLayout {
                RowLayout {
                    CoreLabel {
                        text: "Status: "
                        Layout.alignment: Qt.AlignRight
                    }
                    CoreLabelSelect {
                        Layout.fillWidth: true
                        text: "Running"
                    }
                }
                RowLayout {
                    CoreLabel {
                        text: "Port: "
                        Layout.alignment: Qt.AlignRight
                    }
                    CoreTextField {
                        Layout.fillWidth: true
                        text: "12345"
                    }
                    CoreSwitch {
                        text: "auto"
                    }
                }

                CoreButton {
                    text: "Stop"
                }
            }
        }

        Item {
            Layout.fillHeight: true
        }
    }
}
