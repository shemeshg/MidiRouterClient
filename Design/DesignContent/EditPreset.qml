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

            function setMidiControlData(control, data) {
                control.portName = data.presetMidiControlOnPortNameId.currentText;
                control.eventTypeId = data.presetMidiControlOnEventTypeId.currentValue;
                control.channel = data.presetMidiControlOnChannelId.currentValue;
                data.presetMidiControlOnData1Id.accepted();
                control.data1 = data.presetMidiControlOnData1Id.currentValue;
                data.presetMidiControlOnData2Id.accepted();
                control.data2 = data.presetMidiControlOnData2Id.currentValue;
            }

            onClicked: {
                editedPreset.name = nameId.text;
                editedPreset.isSendAllUserControls = isSendAllUserControlsId.checked;
                setMidiControlData(editedPreset.midiControlOn, editPresetControlOnId);
                setMidiControlData(editedPreset.midiControlOff, editPresetControlOffId);
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
