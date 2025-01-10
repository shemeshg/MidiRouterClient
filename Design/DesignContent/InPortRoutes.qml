import QtQuick
import Design
import Core
import QtQuick.Layouts
import QtQuick.Controls

ColumnLayout {
    property var midiRouteInput: Constants.balData.midiClientConnection.userDataConfig.activePreset.getInputOrCreateByName(inPortsLoaderId.inPortName)
    CoreButton {
        text: "back"
        onClicked: {
            inPortsId.state = "InPortsList";
        }
    }
    RowLayout {
        CoreLabel {
            text: "Routes InPort: " + midiRouteInput.midiInputName
        }
    }
    CoreLabel {
        text: "<H1>Chains</h1>"
    }
    CoreButton {
        text: "add chain"
        onClicked: midiRouteInput.addMidiRouterChain(`chain ${midiRouteInput.midiRouterChains.length + 1}`)
    }
    Repeater {
        model: midiRouteInput.midiRouterChains
        ColumnLayout {
            RowLayout {

                CoreComboBox {
                    id: addFilterCombo
                    Layout.fillWidth: true
                    textRole: "text"
                    valueRole: "value"
                    model: [
                        { value: "", text: "" },
                        { value: "",text: "- To output" },
                        { value: "midi", text: "Midi" },
                        { value: "console",text: "Console" },
                         { value: "network",  text: "Network" },
                         { text: "- Filter and modify" },
                         { value: "filter" ,text: "Filter and transform" },
                         { value: "Schedule" ,text: "Schedule" },
                    ]

                    delegate: ItemDelegate {
                        text: modelData.text
                        enabled: !modelData.text.startsWith("-")
                    }
                }
                CoreButton {
                    text: "Add Filter"
                    onClicked: {
                        if (addFilterCombo.currentValue === "midi"){
                            modelData.addFilterMidiDestination("test 1")
                            console.log("created midi")
                        }

                    }
                }
            }


            CoreLabel {
                text: `${modelData.name}  ${modelData.isEasyConfig ? "auto EasyConfig" : ""}  ${modelData.isRunForPresetOnAndOff?
                                                                     "auto Preset on/off": ""}`
            }
            CoreLabel {
                text: "Filters : "
            }
            Repeater {
                model: modelData.midiRoutersFilters
                RowLayout {
                    enum FilterType {
                        TO_MIDI_DESTINATION,
                        TO_CONSOLE,
                        TO_NETWORK,
                        SCHEDULE_TO,
                        FILTER_AND_TRANSFORM
                    }
                    function getFilterTypeString(filterType) {
                        switch (filterType) {
                            case FilterType.TO_MIDI_DESTINATION:
                                return "TO_MIDI_DESTINATION";
                            case FilterType.TO_CONSOLE:
                                return "TO_CONSOLE";
                            case FilterType.TO_NETWORK:
                                return "TO_NETWORK";
                            case FilterType.SCHEDULE_TO:
                                return "SCHEDULE_TO";
                            case FilterType.FILTER_AND_TRANSFORM:
                                return "FILTER_AND_TRANSFORM";
                            default:
                                return "UNKNOWN";
                        }
                    }
                    CoreLabel {
                        text: getFilterTypeString(modelData.filterType) + ": "
                    }
                    CoreLabel {
                        text: modelData.name
                    }
                    CoreButton {
                        text: "edit"
                    }
                    CoreButton {
                        text: "del"
                    }
                }
            }

            CoreButton {
                text: "Del"
                onClicked: midiRouteInput.delMidiRouterChain(index);
            }
        }

    }
}
