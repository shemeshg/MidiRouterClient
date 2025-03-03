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
            CoreLabel {
                text: modelData
            }
        }
    }
}
