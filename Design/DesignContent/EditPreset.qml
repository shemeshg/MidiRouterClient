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
                editPresetControlOnId.setMidiControlData(editedPreset.midiControlOn);
                editPresetControlOffId.setMidiControlData(editedPreset.midiControlOff);

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
    CoreLabel {
        text: "<H2>Midi control on</h2>"
    }
    EditPresetControl {
        id: editPresetControlOnId
        midiControl: editedPreset.midiControlOn
    }

    CoreLabel {
        text: "<H2>Midi control off</h2>"
    }
    EditPresetControl {
        id: editPresetControlOffId
        midiControl: editedPreset.midiControlOff
    }
}
