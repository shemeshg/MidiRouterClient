import QtQuick
import QtQuick.Controls
import Design
import Core
import QtQuick.Layouts
import UiComp

ColumnLayout {
    property string inputName: ""
    property var midiRouteInput: ({})
    Component.onCompleted: {
        inputName = inPortsLoaderId.inPortName
        midiRouteInput = Constants.balData.midiClientConnection.userDataConfig.activePreset.getInputOrCreateByName(inputName)
    }


    GroupBox {
        Layout.margins:  Constants.font.pixelSize
        Layout.fillWidth: true


        RowLayout {
            anchors.left: parent.left
            anchors.right: parent.right

            UiBtnBack {
                onClicked: {
                    isSubForm = false
                    inPortsId.state = "InPortsList";
                    console.log(JSON.stringify(midiRouteInput.monitor.isMonitored))
                }
            }
            Item {
                Layout.fillWidth: true
            }
            CoreLabel {
                text: midiRouteInput.midiInputName
            }
            Item {
                Layout.fillWidth: true
            }
            CoreLabel {
                text: "Monitor"
            }
        }
    }


    RowLayout{
        Layout.leftMargin:   Constants.font.pixelSize
        Layout.rightMargin:   Constants.font.pixelSize
        CoreSwitch {
            text: "Monitored"
            checked: midiRouteInput.monitor.isMonitored
            onToggled: {
                midiRouteInput.monitor.isMonitored = checked;
                Constants.balData.applyConfig(() => {
                    console.log("client says we have finished applay config");
                });
            }
        }
        CoreTextField {
            text: midiRouteInput.monitor.logLen
            onTextEdited: {
                midiRouteInput.monitor.logLen = Number(text) > 0 ? Number(text) : 1
                Constants.balData.applyConfig(() => {
                    console.log("client says we have finished applay config");
                });
            }
        }
    }
    Repeater {
        Layout.leftMargin:   Constants.font.pixelSize
        Layout.rightMargin:   Constants.font.pixelSize
        model: midiRouteInput.monitor.logItems        
        RowLayout {
            CoreTextArea {
                Layout.fillWidth: true
                readOnly: true
                text: modelData
            }
        }
    }
}
