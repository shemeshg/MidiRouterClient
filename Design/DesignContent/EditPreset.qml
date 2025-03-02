import QtQuick
import QtQuick.Controls
import Design
import Core
import QtQuick.Layouts

ColumnLayout {
    property var editedPreset: Constants.balData.midiClientConnection.userDataConfig.midiRoutePresets[presetsLoaderId.presetIndex]
    GroupBox {
        Layout.margins:  Constants.font.pixelSize
        Layout.fillWidth: true

        RowLayout {
            anchors.left: parent.left
            anchors.right: parent.right
            CoreLabel {
                text: "Edit Preset "
            }
            Item {
                Layout.fillWidth: true
            }
            CoreButton {
                text: "back"



                onClicked: {
                    editPresetControlOnId.setMidiControlData(editedPreset.midiControlOn);
                    editPresetControlOffId.setMidiControlData(editedPreset.midiControlOff);
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
}
