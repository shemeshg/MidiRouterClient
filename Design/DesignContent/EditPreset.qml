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
                editPresetControlOnId.setMidiControlData(editedPreset.midiControlOn);
                editPresetControlOffId.setMidiControlData(editedPreset.midiControlOff);

                if (editedPreset.midiControlOn.portName){
                    editedPreset.getInputOrCreateByName(editedPreset.midiControlOn.inPortName)
                }
                if (editedPreset.midiControlOff.portName){
                    editedPreset.getInputOrCreateByName(editedPreset.midiControlOff.inPortName)
                }
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
