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
                title: "Presets"


            }
            Item {
                Layout.fillWidth: true
            }
            UiBtnAdd {
                onClicked: {
                    Constants.balData.midiClientConnection.userDataConfig.addPreset();
                }

            }
        }
    }
    Repeater {
        Layout.fillWidth: true
        model: Constants.balData.midiClientConnection.userDataConfig.midiRoutePresets

        RowLayout {
            Layout.leftMargin:  Constants.font.pixelSize
            Layout.rightMargin:  Constants.font.pixelSize
            CoreSwitch {
                text: ""
                checked: modelData.isEnabled
                onToggled: {
                    modelData.isEnabled = checked;
                }
            }
            UiBtnEdit {
                onClicked: {
                    presetsLoaderId.presetIndex = index;
                    isSubForm = true
                    presets.state = "EditPreset";

                }
            }
            CoreLabel {
                text: modelData.name
            }
            CoreLabel {
                text: "*"
                visible: index === Constants.balData.midiClientConnection.userDataConfig.activePresetID
            }
            CoreButton {
                text: "select"
                visible: index !== Constants.balData.midiClientConnection.userDataConfig.activePresetID
                onClicked: {
                    Constants.balData.midiClientConnection.userDataConfig.setActivePreset(index, true);
                }
            }
            UiBtnDel {
                visible: Constants.balData.midiClientConnection.userDataConfig.midiRoutePresets.length > 1 && index !== Constants.balData.midiClientConnection.userDataConfig.activePresetID
                onClicked: {
                    Constants.balData.midiClientConnection.userDataConfig.deletePreset(index);
                }
            }

        }
    }



}
