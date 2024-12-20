import QtQuick
import Design
import Core
import QtQuick.Layouts

ColumnLayout {
        required property var midiControl;
        property alias presetMidiControlOnPortNameId: presetMidiControlOnPortNameId;
        property alias presetMidiControlOnEventTypeId: presetMidiControlOnEventTypeId;
        property alias presetMidiControlOnChannelId: presetMidiControlOnChannelId;
        property alias presetMidiControlOnData1Id: presetMidiControlOnData1Id;
        property alias presetMidiControlOnData2Id: presetMidiControlOnData2Id;

        RowLayout {
            CoreLabel {
                text: "portName"
            }
            CoreComboBox {
                id: presetMidiControlOnPortNameId
                Layout.fillWidth: true
                model: ["", ...Constants.balData.midiClientConnection.userDataConfig.connectedOutPorts]

                Component.onCompleted: {
                    var index = model.indexOf(midiControl.portName);
                    if (index !== -1) {
                        currentIndex = index;
                    }
                }
            }
        }
        RowLayout {
            CoreLabel {
                text: "Event"
            }
            MidiControlEventType {
                id: presetMidiControlOnEventTypeId
                Layout.fillWidth: true
                Component.onCompleted: {
                    currentIndex = midiControl.eventTypeId;
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
            }
        }
        RowLayout {
            CoreLabel {
                text: "Data1"
            }
            MidiControlData {
                id: presetMidiControlOnData1Id
                Component.onCompleted: {
                    currentIndex = model.findIndex(item => item.value === midiControl.data1);
                }
            }
        }
        RowLayout {
            CoreLabel {
                text: "Data2"
            }
            MidiControlData {
                id: presetMidiControlOnData2Id
                Component.onCompleted: {
                    currentIndex = model.findIndex(item => item.value === midiControl.data2);
                }
            }
        }
    }
