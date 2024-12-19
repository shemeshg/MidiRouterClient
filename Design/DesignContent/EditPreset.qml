import QtQuick
import Design
import Core
import QtQuick.Layouts

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
