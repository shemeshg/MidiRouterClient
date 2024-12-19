import QtQuick
import Design
import Core
import QtQuick.Layouts


ColumnLayout {
            id: presets
            Layout.fillWidth: true
            CoreButton {
                text: "applayConfig"
                onClicked: {
                    Constants.balData.applyConfig(() => {
                                                          console.log(
                                                              "client says we have finished applay config" )
                                                      })
                }
            }
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
                    CoreButton {
                        text: "select"
                        visible: index !== Constants.balData.midiClientConnection.userDataConfig.activePresetID
                        onClicked: {
                            Constants.balData.midiClientConnection.userDataConfig.activePresetID = index;
                        }
                    }
                }
            }

            CoreButton {
                text: "add preset"
                onClicked: {
                    Constants.balData.midiClientConnection.userDataConfig.addPreset();
                }
            }
            CoreLabel {
                text: "preset 1 midiControlOn()" + JSON.stringify(Constants.balData.midiClientConnection.userDataConfig.activePreset
                    //.midiControlOn
                )
            }
        }
