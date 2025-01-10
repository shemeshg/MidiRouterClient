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
                }
            }


            CoreLabel {
                text: `${modelData.name}  ${modelData.isEasyConfig ? "auto EasyConfig" : ""}  ${modelData.isRunForPresetOnAndOff?
                                                                     "auto Preset on/off": ""}`
            }
            CoreLabel {
                text: "Filters : " + JSON.stringify(modelData.midiRoutersFilters)
            }
            CoreButton {
                text: "Del"
                onClicked: midiRouteInput.delMidiRouterChain(index);
            }
        }

    }
}
