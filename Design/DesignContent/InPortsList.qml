import QtQuick
import Design
import Core
import QtQuick.Layouts
import UiComp

Column {
    UiTitle {
        title: "Connected in ports"
    }

    Repeater {
        model: Constants.balData.midiClientConnection.userDataConfig.connectedInPorts
        RowLayout {
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
            CoreLabel {
                text: modelData
            }
        }
    }
}
