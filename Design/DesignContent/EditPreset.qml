import QtQuick
import Design
import Core
import QtQuick.Layouts

ColumnLayout {
    property var editedPreset: Constants.balData.midiClientConnection.userDataConfig.midiRoutePresets[presetsLoaderId.presetIndex]


    CoreLabel {
        text: "Edit Preset " + presetsLoaderId.presetIndex
    }
    RowLayout {
        CoreButton {
            text: "save"
            onClicked: {
                editedPreset.name = nameId.text;
                editedPreset.isSendAllUserControls = isSendAllUserControlsId.checked;
                editedPreset.midiControlOn.portName = presetMidiControlOnPortNameId.currentText;
                presets.state = "ListPresets";
            }
        }
        CoreButton {
            text: "back"
            onClicked: {
                presets.state = "ListPresets";
            }
        }
    }
    RowLayout {
        CoreLabel {
            text: "Name"
        }
        CoreTextField {
            id: nameId
            text: editedPreset.name
        }
    }
    CoreSwitch {
        id: isSendAllUserControlsId
        text: "isSendAllUserControls"
        checked: editedPreset.isSendAllUserControls

    }
    CoreLabel {
        text: "<H2>Midi control on</h2>"
    }
    RowLayout{
        CoreLabel {
            text: "portName"
        }
        CoreComboBox {
            id: presetMidiControlOnPortNameId
            model: ["", ...Constants.balData.midiClientConnection.userDataConfig.connectedOutPorts]
                        
            Component.onCompleted: {
                var index = model.indexOf(editedPreset.midiControlOn.portName);
                if (index !== -1) {
                    currentIndex = index;
                }
            }
        }
    }
}
