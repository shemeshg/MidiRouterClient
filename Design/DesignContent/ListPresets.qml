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
                    Constants.balData.applyConfig(() => {
                    });
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
                hooverText: "select"
                icon.name: "select"
                icon.source: Qt.resolvedUrl("icons/ink_selection_24dp_E3E3E3_FILL0_wght400_GRAD0_opsz24.svg")
                icon.color: CoreSystemPalette.buttonText
                palette.buttonText: CoreSystemPalette.buttonText


                visible: index !== Constants.balData.midiClientConnection.userDataConfig.activePresetID
                onClicked: {
                    Constants.balData.midiClientConnection.userDataConfig.setActivePreset(index, true);
                    Constants.balData.applyConfig(() => {
                    });
                }
            }
            UiBtnDel {
                visible: Constants.balData.midiClientConnection.userDataConfig.midiRoutePresets.length > 1 && index !== Constants.balData.midiClientConnection.userDataConfig.activePresetID
                onClicked: {
                    Constants.balData.midiClientConnection.userDataConfig.deletePreset(index);
                }
            }
            Item {
                Layout.fillWidth: true
            }

            UiBtnUp {
                visible: Constants.balData.midiClientConnection.userDataConfig.midiRoutePresets.length > 1
                onClicked: {
                    Constants.balData.midiClientConnection.userDataConfig.movePreset(index, index - 1);
                }
            }

        }
    }



}
