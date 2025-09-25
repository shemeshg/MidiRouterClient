import QtQuick
import Design
import Core
import QtQuick.Layouts
import QtQuick.Controls
import UiComp

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

    GroupBox {
        Layout.margins:  Constants.font.pixelSize
        Layout.fillWidth: true

        RowLayout {
            anchors.left: parent.left
            anchors.right: parent.right

            UiBtnBack {
                onClicked: {
                    isSubForm = false
                    inPortsId.state = "InPortsList";
                }
            }
            Item {
                Layout.fillWidth: true
            }
            CoreLabel {
                text: midiRouteInput.midiInputName
            }
            Item {
                Layout.fillWidth: true
            }
            CoreLabel {
                text: "Edit Routes"
            }
        }
    }

    GroupBox {
        Layout.margins:  Constants.font.pixelSize
        Layout.fillWidth: true

        RowLayout {
            Layout.leftMargin: Constants.font.pixelSize
            Layout.rightMargin: Constants.font.pixelSize
            anchors.left: parent.left
            anchors.right: parent.right
            UiTitle {
                title: "Chains"


            }
            Item {
                Layout.fillWidth: true
            }
            UiBtnAdd {
                onClicked: {
                    midiRouteInput.addMidiRouterChain(`chain ${midiRouteInput.midiRouterChains.length + 1}`)
                }

            }
        }
    }


    CoreTextField {
        Layout.margins:  Constants.font.pixelSize
        id: filterByDescription
        Layout.fillWidth: true
        placeholderText: "RegEx filter by description ex. tag1|tag2"
    }
    function testFilterByDescription(userInput) {
        const searchRegExp = new RegExp(filterByDescription.text,"i");
        return searchRegExp.test(userInput);
    }

    Repeater {
        model: midiRouteInput.midiRouterChains


        GroupBox {
            Layout.margins:  Constants.font.pixelSize
            Layout.fillWidth: true
            property var currentChain: modelData
            property bool chainEnabled : !modelData.isEasyConfig && !modelData.isRunForPresetOnAndOff

            visible: testFilterByDescription(modelData.name)
            ColumnLayout {

                anchors.left: parent.left
                anchors.right: parent.right


                RowLayout {
                    Layout.leftMargin: Constants.font.pixelSize
                    Layout.rightMargin: Constants.font.pixelSize
                    CoreTextField {
                        text: modelData.name
                        Layout.fillWidth: true
                        onTextEdited: ()=>{
                                        modelData.name = text
                                      }
                        enabled: chainEnabled
                    }

                    Item {
                        Layout.fillWidth: true
                    }
                    UiBtnDel {
                        onClicked: midiRouteInput.delMidiRouterChain(index);
                        enabled: chainEnabled
                    }
                    CoreLabel {
                        text: `${modelData.isEasyConfig ? "auto EasyConfig" : ""}  ${modelData.isRunForPresetOnAndOff?
                                                              "auto Preset on/off": ""}`
                    }
                }
                RowLayout {
                    Layout.leftMargin: Constants.font.pixelSize
                    Layout.rightMargin: Constants.font.pixelSize
                    CoreLabel {
                        text: "Filter"
                    }

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
                        enabled: chainEnabled
                    }
                    UiBtnAdd {
                        enabled: chainEnabled
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

                ColumnLayout{
                    Layout.leftMargin: Constants.font.pixelSize
                    Layout.rightMargin: Constants.font.pixelSize
                    CoreLabel {
                        text: "Filters : "
                    }
                    Repeater {

                        model: modelData.midiRoutersFilters
                        RowLayout {
                            property var currentMidiRoutersFilter: modelData
                            UiBtnEdit {
                                onClicked: {
                                    inPortsRoutesLoaderId.filterObj = modelData;
                                    inPortsRoutesLoaderId.isEnabled = chainEnabled;
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
                            UiBtnDel {
                                onClicked: {
                                    currentChain.delMidiRoutersFilter(index)
                                }
                                enabled: chainEnabled
                            }
                            CoreLabel {
                                text: getFilterTypeString(modelData.filterType) + ": "
                            }
                            CoreLabel {
                                text: modelData.name
                            }

                        }
                    }
                }

            }
        }

    }
}
