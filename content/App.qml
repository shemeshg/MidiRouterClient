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

        width: parent.width
        height: parent.height

        FormGroupBox {
            Layout.margins: Constants.font.pixelSize

            title: "<h3>Client</h3>"
            body: ColumnLayout {
                RowLayout {
                    CoreLabel {
                        text: "Status: "
                        Layout.alignment: Qt.AlignRight
                    }
                    CoreLabelSelect {
                        Layout.fillWidth: true
                        text: Constants.balData.midiClientConnection.serverStatusText
                    }
                }
                RowLayout {
                    visible: connectBtn.visible
                    CoreLabel {
                        visible: !clientConnectLocal.checked
                        text: "Server name: "
                    }
                    CoreTextField {
                        visible: !clientConnectLocal.checked
                        Layout.fillWidth: true
                        text: "localhost"
                    }
                    Item {
                        Layout.fillWidth: true
                        visible: clientConnectLocal.checked
                    }
                    CoreSwitch {
                        id: clientConnectLocal
                        text: "local"
                    }
                }
                RowLayout {
                    visible: !clientConnectLocal.checked && connectBtn.visible

                    CoreLabel {
                        text: "Port: "
                    }
                    CoreTextField {

                        Layout.fillWidth: true
                        text: "12345"
                    }
                }
                RowLayout {
                    visible: Constants.balData.midiClientConnection.serverStatus
                             !== Constants.ServerStatus.STARTING
                    CoreButton {
                        id: connectBtn
                        visible: Constants.balData.midiClientConnection.serverStatus
                                 === Constants.ServerStatus.STOPPED
                                 || Constants.balData.midiClientConnection.serverStatus
                                 === Constants.ServerStatus.FAILED
                        text: "Connect"
                        onClicked: {
                            Constants.balData.setAsyncServerStatusAndText(
                                        Constants.ServerStatus.STARTING, () => {
                                            Constants.balData.startClient(
                                                "localhost", 12345)
                                        })
                        }
                    }
                    CoreButton {
                        id: disconnectBtn
                        visible: Constants.balData.midiClientConnection.serverStatus
                                 === Constants.ServerStatus.RUNNING
                        text: "Disconnect"
                        onClicked: {
                            Constants.balData.stopClient()
                        }
                    }


                    /*
                    CoreButton {
                        text: "test"
                        onClicked: {
                            Constants.balData.testDummyDelete(x => {
                                                                  console.log(
                                                                      "we have " + x)
                                                              })
                        }
                    }
                    */
                    Item {
                        visible: connectBtn.visible
                        Layout.fillWidth: true
                    }

                    CoreSwitch {
                        visible: connectBtn.visible
                        text: "auto"
                    }
                }
            }
        }

        FormGroupBox {
            Layout.margins: Constants.font.pixelSize
            title: qsTr("<h3>Server</h3>")
            body: ColumnLayout {
                RowLayout {
                    CoreLabel {
                        text: "Status: "
                        Layout.alignment: Qt.AlignRight
                    }
                    CoreLabelSelect {
                        Layout.fillWidth: true
                        text: Constants.balData.isServerRunning ? "Running " + Constants.balData.serverPort : "Stopped"
                    }
                }
                RowLayout {
                    visible: !Constants.balData.isServerRunning
                    CoreLabel {
                        text: "Port: "
                        Layout.alignment: Qt.AlignRight
                    }
                    CoreTextField {
                        Layout.fillWidth: true
                        text: Constants.balData.reqServerPortNumber
                        id: serverPortNumber
                        visible: !isAutoPort.checked
                    }
                    Item {
                        Layout.fillWidth: true
                        visible: isAutoPort.checked
                    }

                    CoreSwitch {
                        id: isAutoPort
                        text: "auto"
                    }
                }
                RowLayout {
                    visible: !Constants.balData.isServerRunning
                    CoreButton {
                        text: "start"
                        enabled: Number.isInteger(Number(serverPortNumber.text))
                                 && (serverPortNumber.text > 0
                                     || isAutoPort.checked)

                        onClicked: {
                            let port = isAutoPort.checked ? 0 : Number(
                                                                serverPortNumber.text)

                            Constants.balData.startServer(port)
                            if (isAutoPort.checked) {
                                serverPortNumber.text = Constants.balData.serverPort
                                isAutoPort.checked = false
                            }
                        }
                    }
                    Item {
                        Layout.fillWidth: true
                    }
                    CoreSwitch {
                        text: "auto"
                    }
                }
                CoreButton {
                    visible: Constants.balData.isServerRunning
                    text: "stop"
                    onClicked: {
                        Constants.balData.stopServer()
                    }
                }
            }
        }

        Item {
            Layout.fillHeight: true
        }
    }
}
