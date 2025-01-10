import QtQuick
import Design
import Core
import QtQuick.Layouts
import QtQuick.Controls

ColumnLayout {
    property var midiRouteInput: Constants.balData.midiClientConnection.userDataConfig.activePreset.getInputOrCreateByName(inPortsLoaderId.inPortName)


    function getFilterTypeString(filterType) {
        switch (filterType) {
            case 0:
                return "TO_MIDI_DESTINATION";
            case 1:
                return "TO_CONSOLE";
            case 2:
                return "TO_NETWORK";
            case 3:
                return "SCHEDULE_TO";
            case 4:
                return "FILTER_AND_TRANSFORM";
            default:
                return "UNKNOWN";
        }
    }

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
            property var currentChain: modelData
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
                    property var currentMidiRoutersFilter: modelData
                    CoreLabel {
                        text: getFilterTypeString(modelData.filterType) + ": "
                    }
                    CoreLabel {
                        text: modelData.name
                    }
                    CoreButton {
                        text: "edit"
                        onClicked: {
                            if (currentMidiRoutersFilter.filterType === 0){
                                console.log("Edit TO_MIDI_DESTINATION")
                            }
                        }
                    }
                    CoreButton {
                        text: "del"
                        onClicked: {
                            currentChain.delMidiRoutersFilter(index)
                        }

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
