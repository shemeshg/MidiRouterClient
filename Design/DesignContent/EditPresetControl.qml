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
        ColumnLayout {
            visible: presetMidiControlOnPortNameId.currentText !== ""
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
    }
