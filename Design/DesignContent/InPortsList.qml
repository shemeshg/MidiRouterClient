import QtQuick
import Design
import Core
import QtQuick.Layouts

Column {
        CoreLabel {
            text: "In ports"
        }
        CoreButton {
            onClicked: {
                console.log(JSON.stringify(Constants.balData.midiClientConnection.userDataConfig.getJson()));

                dummy.text = JSON.stringify(Constants.balData.midiClientConnection.userDataConfig.midiRoutePresets[0].midiRouteInputs);
            }
        }

        CoreLabel {
            text: "<h1>Connected in ports</h1>"
        }
        Repeater {
            model: Constants.balData.midiClientConnection.userDataConfig.connectedInPorts
            RowLayout {
                CoreLabel {
                    text: modelData
                }
                CoreButton {
                    text: "Settings"
                    onClicked: {
                        inPortsLoaderId.inPortName = modelData;
                        inPortsId.state = "InPortSettings";
                    }
                }
                CoreButton {
                    text: "Routes"
                    onClicked: {
                        inPortsLoaderId.inPortName = modelData;
                        inPortsId.state = "InPortRoutes";
                    }
                }
                CoreButton {
                    text: "EasyConfig"
                    onClicked: {
                        inPortsLoaderId.inPortName = modelData;
                        inPortsId.state = "InPortEasyConfig";
                    }
                }
                CoreButton {
                    text: "Monitor"
                    onClicked: {
                        inPortsLoaderId.inPortName = modelData;
                        inPortsId.state = "InPortMonitor";
                    }
                }
            }
        }
        CoreTextArea {
            id: dummy
            wrapMode: Text.WordWrap
        }
    }
