import QtQuick
import Design
import Core
import QtQuick.Layouts
import QtQuick.Controls

ColumnLayout {
    function getFilterTypeString(filterType) {
        switch (filterType) {
        case Constants.FilterType.TO_MIDI_DESTINATION:
            return "TO_MIDI_DESTINATION";
        case Constants.FilterType.TO_CONSOLE:
            return "TO_CONSOLE";
        case Constants.FilterType.TO_NETWORK:
            return "TO_NETWORK";
        case Constants.FilterType.SCHEDULE_TO:
            return "SCHEDULE_TO";
        case Constants.FilterType.FILTER_AND_TRANSFORM:
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
                        { value: "fnt" ,text: "Filter and transform" },
                        { value: "schedule" ,text: "Schedule" },
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
                            modelData.addFilterMidiDestination("")
                        } else if (addFilterCombo.currentValue === "console"){
                            modelData.addFilterToConsole(Constants.LogTo.CLIENT,"{}")
                        } else if (addFilterCombo.currentValue === "network"){
                            modelData.addFilterNetworkDestination("localhost",12345,"")
                        } else if (addFilterCombo.currentValue === "schedule"){
                            modelData.addFilterFilterSchedule(Constants.DefferedType.IN_SPP ,0)
                        } else if (addFilterCombo.currentValue === "fnt"){
                            modelData.addFilterAndTransform("Filer",
                                                            Constants.ConditionAction.DELETE_IF_NOT_MET_CONDITION,
                                                            "[[0,16,0]]",
                                                            "[[0,16,0]]",
                                                            "[[0,127,0]]",
                                                            "[[0,127,0]]" )
                        }

                    }
                }
            }


            CoreLabel {
                text: `Chain name: ${modelData.name} uuid: ${modelData.uuid} ${modelData.isEasyConfig ? "auto EasyConfig" : ""}  ${modelData.isRunForPresetOnAndOff?
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
                            inPortsRoutesLoaderId.filterObj = modelData;
                            if (currentMidiRoutersFilter.filterType === Constants.FilterType.TO_MIDI_DESTINATION){
                                inPortRoutesId.state = "InPortsRoutesFilterToMidi"
                            } else if (currentMidiRoutersFilter.filterType === Constants.FilterType.TO_CONSOLE){
                                inPortRoutesId.state = "InPortsRoutesFilterToConsole"
                            } else if (currentMidiRoutersFilter.filterType === Constants.FilterType.TO_NETWORK){
                                inPortRoutesId.state = "InPortsRoutesFilterToNetwork"
                            } else if (currentMidiRoutersFilter.filterType === Constants.FilterType.SCHEDULE_TO){
                                inPortRoutesId.state = "InPortsRoutesFilterSchedule"
                            } else if (currentMidiRoutersFilter.filterType === Constants.FilterType.FILTER_AND_TRANSFORM){
                                inPortRoutesId.state = "InPortsRoutesFilterFnt"
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
