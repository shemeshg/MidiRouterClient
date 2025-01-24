import QtQuick
import Design
import Core
import QtQuick.Layouts
import QtQuick.Controls

ColumnLayout {



    CoreLabel {
        text: "<h1>Routes</h1>"
    }

    CoreButton {
        text: "Add"
        onClicked: {
            midiRouteInput.easyConfig.addEasyConfigRoute()
            console.log(
                        JSON.stringify(midiRouteInput.easyConfig.easyConfigRoutes)
                        )
        }
    }

    Repeater {
        model: midiRouteInput.easyConfig.easyConfigRoutes
        ColumnLayout {
            property bool fromKeyOnOff: [1,2,3].indexOf( fromEvent.currentIndex) > -1

            RowLayout {
                CoreLabel {
                    text: "Destination"
                }
                CoreComboBox {
                    id: nameId
                    Layout.fillWidth: true
                    model: ["", ...Constants.balData.midiClientConnection.userDataConfig.connectedOutPorts]
                    onActivated: {
                        modelData.toDestinationName = currentText
                    }

                    Component.onCompleted: {
                        var index = model.indexOf(modelData.toDestinationName);
                        if (index !== -1) {
                            currentIndex = index;
                        }
                    }
                }
            }
            RowLayout {

                ColumnLayout {
                    CoreLabel {
                        text: "From event"
                    }

                    MidiControlEventType {
                        id: fromEvent
                        implicitWidth: Constants.font.pixelSize * 15
                        Component.onCompleted: {
                            currentIndex = modelData.fromSelectedMidiEventTypeId;
                        }
                        onActivated: {
                            modelData.fromSelectedMidiEventTypeId = currentIndex
                            // auto the other
                            modelData.toSelectedMidiEventTypeId = currentIndex
                            toEvent.currentIndex = currentIndex
                        }
                    }
                }
                ColumnLayout {
                    CoreLabel {
                        text: "From Channel"
                    }
                    MidiControlChannel {
                        Component.onCompleted: {
                            currentIndex = model.findIndex(item => item.value === modelData.fromChannel);
                        }
                        onActivated: {
                            modelData.fromChannel = currentValue
                            // auto the other
                            modelData.toChannel = currentValue
                            toChannel.currentIndex = currentIndex
                        }
                    }
                }
                ColumnLayout{
                    visible: fromKeyOnOff
                    CoreLabel {
                        text: "From Zone"
                    }

                    CoreComboBox {
                        textRole: "text"
                        valueRole: "value"
                        model: [
                            {
                                value: -1,
                                text: "-"
                            },
                            ...midiRouteInput.easyConfig.zoneNames.map((text, index) => {
                                                                           return { value: index, text: text };
                                                                       })]
                        Component.onCompleted: {
                            currentIndex = model.findIndex(item => item.value === modelData.splitRangeId);
                        }
                        onActivated: {
                            modelData.splitRangeId = currentValue
                        }
                    }
                }
            }

            RowLayout {
                ColumnLayout {
                    CoreLabel {
                        text: "To event"
                    }
                    MidiControlEventType {
                        id: toEvent
                        implicitWidth: Constants.font.pixelSize * 15
                        Component.onCompleted: {
                            currentIndex = modelData.toSelectedMidiEventTypeId;
                        }
                        onActivated: {
                            modelData.toSelectedMidiEventTypeId = currentValue
                        }
                    }
                }
                ColumnLayout {
                    CoreLabel {
                        text: "To Channel"
                    }
                    MidiControlChannel {
                        id: toChannel
                        Component.onCompleted: {
                            currentIndex = model.findIndex(item => item.value === modelData.toChannel);
                        }
                        onActivated: {
                            modelData.toChannel = currentValue
                        }
                    }
                }
            }
        }
    }
}

