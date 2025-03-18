import QtQuick
import QtQuick.Controls
import Design
import Core
import QtQuick.Layouts
import UiComp

ColumnLayout {
    id: editPresetId
    property var editedPreset: Constants.balData.midiClientConnection.userDataConfig.midiRoutePresets[presetsLoaderId.presetIndex]

    function save(){
        editPresetControlOnId.setMidiControlData(editedPreset.midiControlOn);
        editPresetControlOffId.setMidiControlData(editedPreset.midiControlOff);
        editPresetControlToggleId.setMidiControlData(editedPreset.midiControlToggle);
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
                    presets.state = "ListPresets";
                }
            }
            Item {
                Layout.fillWidth: true
            }
            CoreLabel {
                text: editedPreset.name
            }
            Item {
                Layout.fillWidth: true
            }
            CoreLabel {
                text: "Edit Preset"
            }
        }
    }


    RowLayout {
        Layout.margins:  Constants.font.pixelSize

        CoreLabel {
            text: "Name"
        }
        CoreTextField {
            id: nameId
            Layout.fillWidth: true
            text: editedPreset.name
            onTextEdited: ()=>{
                             editedPreset.name = nameId.text;
                          }
        }
    }

    GroupBox {

        Layout.margins:  Constants.font.pixelSize
        Layout.fillWidth: true
        ColumnLayout {
            anchors.left: parent.left
            anchors.right: parent.right
            CoreLabel {
                text: "<H2>Midi control on</h2>"
            }
            EditPresetControl {
                id: editPresetControlOnId
                midiControl: editedPreset.midiControlOn
            }
        }
    }

    GroupBox {

        Layout.margins:  Constants.font.pixelSize
        Layout.fillWidth: true
        ColumnLayout {
            anchors.left: parent.left
            anchors.right: parent.right
            CoreLabel {
                text: "<H2>Midi control off</h2>"
            }
            EditPresetControl {
                id: editPresetControlOffId
                midiControl: editedPreset.midiControlOff
            }
        }
    }
    GroupBox {

        Layout.margins:  Constants.font.pixelSize
        Layout.fillWidth: true
        ColumnLayout {
            anchors.left: parent.left
            anchors.right: parent.right
            CoreLabel {
                text: "<H2>Midi control Toggle</h2>"
            }
            EditPresetControl {
                id: editPresetControlToggleId
                midiControl: editedPreset.midiControlToggle
            }
        }
    }
}
