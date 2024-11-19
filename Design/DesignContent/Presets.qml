import QtQuick
import Design
import Core
import QtQuick.Layouts
import QtQuick.Controls

ColumnLayout {
            id: presets
            Layout.fillWidth: true
            CoreButton {
                text: "console.log getJson"
                onClicked: {
                    console.log(
                                JSON.stringify(Constants.balData.midiClientConnection.userDataConfig.getJson())
                                )
                }
            }

            CoreLabel {
                text: "Selected preset id:" + Constants.balData.midiClientConnection.userDataConfig.activePresetID
            }

            Repeater {
                Layout.fillWidth: true
                model: Constants.balData.midiClientConnection.userDataConfig.midiRoutePresets

                RowLayout {
                    CoreLabel {
                        text:   modelData.name
                    }
                    CoreLabel {
                        text: "*"
                        visible: index === Constants.balData.midiClientConnection.userDataConfig.activePresetID
                    }
                }
            }

            CoreLabel {
                text: "preset 1 midiControlOn()" + JSON.stringify(Constants.balData.midiClientConnection.userDataConfig.midiRoutePresets[0].midiControlOn)
            }
        }
