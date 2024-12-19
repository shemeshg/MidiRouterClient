import QtQuick
import Design
import Core
import QtQuick.Layouts

ColumnLayout {
    id: presets
    state: "ListPresets"
    Layout.fillWidth: true

    Loader {
        id: presetsLoaderId
        property int presetIndex: -1
        Layout.fillWidth: true
    }

    Component {
        id: editPresetId
        
        ColumnLayout {
            CoreLabel {
                text: "Edit Preset " + presetsLoaderId.presetIndex
            }
            RowLayout {
                CoreButton {
                    text: "save"
                    onClicked: {
                        Constants.balData.midiClientConnection.userDataConfig.midiRoutePresets[presetsLoaderId.presetIndex].name = 
                                nameId.text;
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
                    text: Constants.balData.midiClientConnection.userDataConfig.midiRoutePresets[presetsLoaderId.presetIndex].name
                }
            }
            
        }
    }

    Component {
        id: listPresetsId
        ColumnLayout {
            CoreButton {
                text: "applayConfig"
                onClicked: {
                    Constants.balData.applyConfig(() => {
                        console.log("client says we have finished applay config");
                    });
                }
            }
            CoreButton {
                text: "console.log getJson"
                onClicked: {
                    console.log(JSON.stringify(Constants.balData.midiClientConnection.userDataConfig.getJson()));
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
                            Constants.balData.midiClientConnection.userDataConfig.setActivePreset(index);
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
            CoreLabel {
                text: "preset 1 midiControlOn()" + JSON.stringify(Constants.balData.midiClientConnection.userDataConfig.activePreset
                //.midiControlOn
                )
            }
        }
    }
    states: [
        State {
            name: "ListPresets"
            when: presets.state === "ListPresets"
            PropertyChanges {
                target: presetsLoaderId
                sourceComponent: listPresetsId
            }
        },
        State {
            name: "EditPreset"
            when: presets.state === "EditPreset"
            PropertyChanges {
                target: presetsLoaderId
                sourceComponent: editPresetId
            }
        }
    ]
}
