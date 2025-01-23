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
                            implicitWidth: Constants.font.pixelSize * 15
                            Component.onCompleted: {
                                currentIndex = modelData.fromSelectedMidiEventTypeId;
                            }
                            onActivated: {
                                modelData.fromSelectedMidiEventTypeId = currentIndex
                            }
                        }

                        CoreLabel {
                            text: "To event"
                        }
                        MidiControlEventType {
                            implicitWidth: Constants.font.pixelSize * 15
                            Component.onCompleted: {
                                currentIndex = modelData.toSelectedMidiEventTypeId;
                            }
                            onActivated: {
                                modelData.toSelectedMidiEventTypeId = currentIndex
                            }
                        }
                    }
                }
            }
        }
}
