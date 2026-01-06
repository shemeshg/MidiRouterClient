import QtQuick
import Design
import Core
import QtQuick.Layouts

ColumnLayout {
    required property var midiControl;

    function setMidiControlData(control) {
        control.portName = presetMidiControlOnPortNameId.currentValue;
        control.eventTypeId = presetMidiControlOnEventTypeId.currentValue;
        control.channel = presetMidiControlOnChannelId.currentValue;
        presetMidiControlOnData1Id.accepted();
        control.data1 = presetMidiControlOnData1Id.currentValue;
        presetMidiControlOnData2Id.accepted();
        control.data2 = presetMidiControlOnData2Id.currentValue;
    }

    RowLayout {
        CoreLabel {
            text: "Port name"
        }
        ComboBoxOutport {
            id: presetMidiControlOnPortNameId
            Layout.fillWidth: true
            cmbVal: midiControl.portName

            onActivated: {
                editPresetId.save()
            }
        }
    }
    ColumnLayout {
        visible: presetMidiControlOnPortNameId.currentText !== ""
        RowLayout {
            CoreLabel {
                text: "From event"
            }
            MidiControlEventType {
                id: presetMidiControlOnEventTypeId
                Layout.fillWidth: true
                Component.onCompleted: {
                    currentIndex = midiControl.eventTypeId;
                }
                onActivated: {
                    editPresetId.save()
                }
            }
        }
        RowLayout {
            CoreLabel {
                text: "Channel"
            }
            MidiControlChannel {
                id: presetMidiControlOnChannelId
                Component.onCompleted: {
                    currentIndex = model.findIndex(item => item.value === midiControl.channel);
                }
                onActivated: {
                    editPresetId.save()
                }
            }
        }
        RowLayout {
            CoreLabel {
                text: "Data1"
            }
            MidiControlData {
                id: presetMidiControlOnData1Id
                property bool processing: true
                Component.onCompleted: {
                    currentIndex = model.findIndex(item => item.value === midiControl.data1);
                }

                onActivated: {
                    editPresetId.save()
                }

            }
            CoreTextField {
                visible: midiControl.eventTypeId === 7 //NRPN event type
                text: midiControl.data1
                onTextEdited: {
                    midiControl.data1 = (!isNaN(text) && text.trim() !== "") ? Number(text) : -1;
                }
            }
        }
        RowLayout {
            CoreLabel {
                text: "Data2"
            }
            MidiControlData {
                id: presetMidiControlOnData2Id
                property bool processing: true
                Component.onCompleted: {
                    currentIndex = model.findIndex(item => item.value === midiControl.data2);
                }
                onActivated: {
                    editPresetId.save()
                }
            }
            CoreTextField {
                visible: midiControl.eventTypeId === 7 //NRPN event type
                text: midiControl.data2
                onTextEdited: {
                    midiControl.data2 = (!isNaN(text) && text.trim() !== "") ? Number(text) : -1;
                }
            }
        }
    }
}
