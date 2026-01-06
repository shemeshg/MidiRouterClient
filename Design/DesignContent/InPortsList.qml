import QtQuick
import QtQuick.Controls
import Design
import Core
import QtQuick.Layouts
import UiComp

ColumnLayout {

    GroupBox {
        Layout.margins:  Constants.font.pixelSize
        Layout.fillWidth: true
        RowLayout {

            anchors.left: parent.left
            anchors.right: parent.right
            UiTitle {
                title: "Connected in ports"
            }
        }
    }


    Repeater {
        model: Constants.balData.midiClientConnection.userDataConfig.connectedInPorts
        RowLayout {
            Layout.leftMargin:  Constants.font.pixelSize
            Layout.rightMargin:  Constants.font.pixelSize
            CoreButton {
                text: "Settings"
                onClicked: {
                    inPortsLoaderId.inPortName = modelData;
                    isSubForm = true
                    inPortsId.state = "InPortSettings";
                }
            }
            CoreButton {
                text: "Routes"
                onClicked: {
                    inPortsLoaderId.inPortName = modelData;
                    isSubForm = true
                    inPortsId.state = "InPortRoutes";
                }
            }
            CoreButton {
                text: "EasyConfig"
                onClicked: {
                    isSubForm = true
                    inPortsLoaderId.inPortName = modelData;
                    isEasyConfigForm = true
                    inPortsId.state = "InPortEasyConfig";
                }
            }
            CoreButton {
                text: "Monitor"
                onClicked: {
                    inPortsLoaderId.inPortName = modelData;
                    isSubForm = true
                    inPortsId.state = "InPortMonitor";
                }
            }
            CoreLabel {
                text: modelData
            }
        }
    }
    function getDisconnectedPorts(){
        let currentPresetInputs = Constants.balData.midiClientConnection.userDataConfig.activePreset.midiRouteInputs.map(row=>{return row.midiInputName})

        return currentPresetInputs.filter(item=>{return !Constants.balData.midiClientConnection.userDataConfig.connectedInPorts.includes(item)});
    }

    CoreLabel {
        text: "<h3>Not connected</h3>"
    }
    Repeater {
        model: getDisconnectedPorts()
        RowLayout {
            Layout.leftMargin:  Constants.font.pixelSize
            Layout.rightMargin:  Constants.font.pixelSize
            CoreButton {
                text: "Settings"
                onClicked: {
                    inPortsLoaderId.inPortName = modelData;
                    isSubForm = true
                    inPortsId.state = "InPortSettings";
                }
            }
            CoreButton {
                text: "Routes"
                onClicked: {
                    inPortsLoaderId.inPortName = modelData;
                    isSubForm = true
                    inPortsId.state = "InPortRoutes";
                }
            }
            CoreButton {
                text: "EasyConfig"
                onClicked: {
                    isSubForm = true
                    inPortsLoaderId.inPortName = modelData;
                    isEasyConfigForm = true
                    inPortsId.state = "InPortEasyConfig";
                }
            }
            CoreButton {
                text: "Del"
                onClicked: {
                    Constants.balData.midiClientConnection.userDataConfig.activePreset.delInputByName(modelData)
                }
            }
            CoreLabel {
                text: "❗ " + modelData
            }
        }
    }

}
