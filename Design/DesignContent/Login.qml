import QtQuick
import Design
import Core
import QtQuick.Layouts


ColumnLayout {
            id: login
            Layout.fillWidth: true

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
                        visible: Constants.balData.midiClientConnection.serverStatus
                                 !== Constants.ServerStatus.STARTING
                        CoreButton {
                            id: connectBtn
                            enabled: Number.isInteger(Number(clientPortNumber.text))
                                     && (clientPortNumber.text > 0)
                            visible: !isAutoConnectClient.checked
                                     && (Constants.balData.midiClientConnection.serverStatus
                                         === Constants.ServerStatus.STOPPED
                                         || Constants.balData.midiClientConnection.serverStatus
                                         === Constants.ServerStatus.FAILED)
                            text: "Connect"
                            onClicked: {
                                Constants.balData.setAsyncServerStatusAndText(
                                            Constants.ServerStatus.STARTING, () => {
                                                Constants.balData.startClient()
                                            })
                                console.log(JSON.stringify(Constants.balData))
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
                            visible: isAutoConnectClient.visible
                            Layout.fillWidth: true
                        }

                        CoreSwitch {
                            id: isAutoConnectClient
                            visible: (Constants.balData.midiClientConnection.serverStatus
                                      === Constants.ServerStatus.STOPPED
                                      || Constants.balData.midiClientConnection.serverStatus
                                      === Constants.ServerStatus.FAILED)
                            text: "auto"
                            onToggled: {
                                Constants.balData.saveIsAutoConnectClient(checked)
                                if (checked) {
                                    Constants.balData.setAsyncServerStatusAndText(
                                                Constants.ServerStatus.STARTING,
                                                () => {
                                                    Constants.balData.startClient()
                                                })
                                }
                            }

                            checked: Constants.balData.isAutoConnectClient
                        }
                    }
                    RowLayout {
                        visible: connectBtn.visible
                        CoreLabel {
                            visible: !isClientConnectLocal.checked
                            text: "Server name: "
                        }
                        CoreTextField {
                            id: clientServerName
                            visible: !isClientConnectLocal.checked
                            Layout.fillWidth: true
                            text: Constants.balData.clientServerName
                            onTextEdited: {
                                Constants.balData.saveClientServerName(text)
                            }
                        }
                        Item {
                            Layout.fillWidth: true
                            visible: isClientConnectLocal.checked
                        }
                        CoreSwitch {
                            id: isClientConnectLocal
                            checked: Constants.balData.isClientConnectLocal
                            text: "local"
                            onToggled: {
                                Constants.balData.saveIsClientConnectLocal(checked)
                            }
                        }
                    }
                    RowLayout {
                        visible: !isClientConnectLocal.checked && connectBtn.visible

                        CoreLabel {
                            text: "Port: "
                        }
                        CoreTextField {
                            id: clientPortNumber
                            Layout.fillWidth: true
                            text: Constants.balData.clientPortNumber
                            onTextEdited: {
                                Constants.balData.saveClientPortNumber(text)
                            }
                        }
                    }
                }
            }

            FormGroupBox {

                Layout.margins: Constants.font.pixelSize
                title: qsTr("<h3>Server</h3>")
                body: ColumnLayout {
                    id: formGroupBoxServerBody
                    function doServerStart() {
                        let port = isAutoPort.checked ? 0 : Number(
                                                            serverPortNumber.text)

                        Constants.balData.startServer(port)
                        if (isAutoPort.checked) {
                            serverPortNumber.text = Constants.balData.serverPort
                            isAutoPort.checked = false
                        }
                    }

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
                        CoreButton {
                            text: "start"
                            visible: !isAutoStartServer.checked && Number.isInteger(
                                         Number(serverPortNumber.text))
                                     && (serverPortNumber.text > 0
                                         || isAutoPort.checked)

                            onClicked: {
                                formGroupBoxServerBody.doServerStart()
                            }
                        }
                        Item {
                            Layout.fillWidth: true
                        }
                        CoreSwitch {
                            id: isAutoStartServer
                            text: "auto"
                            checked: Constants.balData.isAutoStartServer
                            onToggled: {
                                Constants.balData.saveIsAutoStartServer(checked)
                                if (checked) {
                                    formGroupBoxServerBody.doServerStart()
                                }
                            }
                        }
                    }
                    RowLayout {
                        visible: !Constants.balData.isServerRunning
                                 && !isAutoStartServer.checked
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
                    CoreButton {
                        visible: Constants.balData.isServerRunning
                        text: "stop"
                        onClicked: {
                            Constants.balData.stopServer()
                        }
                    }
                }
                RowLayout {
                    CoreSwitch {
                        id: isSaveConfigOnServer
                        text: "Save config on server"
                        checked: Constants.balData.isSaveConfigOnServer
                        onToggled: {
                            Constants.balData.saveIsSaveConfigOnServer(checked)
                        }
                    }
                    CoreLabel{
                        id: hyperlinkBtn
                        color: CoreSystemPalette.isDarkTheme ? "Light blue" : "Dark blue"
                        text: "link"
                        MouseArea {
                            anchors.fill: parent
                            cursorShape: Qt.PointingHandCursor
                            onClicked: () => {
                                           Qt.openUrlExternally("file://" + Constants.balData.cashFolder());
                                       }
                        }
                    }
                }
            }

        }
