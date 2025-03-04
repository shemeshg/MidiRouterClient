import QtQuick
import Design
import Core
import QtQuick.Layouts

ColumnLayout {
    required property var midiControl;

    function setMidiControlData(control) {
        control.portName = presetMidiControlOnPortNameId.currentText;
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
        CoreComboBox {
            id: presetMidiControlOnPortNameId
            Layout.fillWidth: true
            

            Component.onCompleted: {
                let list = ["", ...Constants.balData.midiClientConnection.userDataConfig.connectedOutPorts]                
                var index = list.indexOf(midiControl.portName);

                presetMidiControlOnPortNameId.model = list
                if (index !== -1) {
                    currentIndex = index;
                }
                
            }

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
        }
    }
}
