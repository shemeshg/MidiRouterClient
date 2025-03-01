import QtQuick
import Design
import Core
import QtQuick.Layouts

ColumnLayout {



            CoreLabel {
                text: "Selected preset id:" + Constants.balData.midiClientConnection.userDataConfig.activePresetID
            }

            Repeater {
                Layout.fillWidth: true
                model: Constants.balData.midiClientConnection.userDataConfig.midiRoutePresets

                RowLayout {
                    CoreLabel {
                        text: modelData.name
                    }
                    CoreLabel {
                        text: "*"
                        visible: index === Constants.balData.midiClientConnection.userDataConfig.activePresetID
                    }
                    CoreButton {
                        text: "select"
                        visible: index !== Constants.balData.midiClientConnection.userDataConfig.activePresetID
                        onClicked: {
                            Constants.balData.midiClientConnection.userDataConfig.setActivePreset(index, true);
                        }
                    }
                    CoreButton {
                        text: "delete"
                        visible: Constants.balData.midiClientConnection.userDataConfig.midiRoutePresets.length > 1 && index !== Constants.balData.midiClientConnection.userDataConfig.activePresetID
                        onClicked: {
                            Constants.balData.midiClientConnection.userDataConfig.deletePreset(index);
                        }
                    }
                    CoreSwitch {
                        text: "isEnabled"
                        checked: modelData.isEnabled
                        onToggled: {
                            modelData.isEnabled = checked;
                        }
                    }
                    CoreButton {
                        text: "edit"
                        onClicked: {
                            presetsLoaderId.presetIndex = index;
                            presets.state = "EditPreset";
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

        }
