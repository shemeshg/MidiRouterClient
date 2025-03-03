import QtQuick
import Design
import Core
import QtQuick.Layouts
import QtQuick.Controls
import UiComp

ColumnLayout {    
    property var midiRouteInput: Constants.balData.midiClientConnection.userDataConfig.activePreset.getInputOrCreateByName(inPortsLoaderId.inPortName)

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
                text: "Input settings"
            }
        }
    }



    RowLayout {
        Layout.margins:  Constants.font.pixelSize
        CoreLabel {
            text: "Ignore types"
        }

        CoreCheckBox {
            id: ignoreTypesMidiSysex
            text: "Sysex"
            checked: midiRouteInput.ignoreTypesMidiSysex
            onToggled:{
                midiRouteInput.ignoreTypesMidiSysex = checked
            }
        }
        CoreCheckBox {
            id: ignoreTypesMidiTime
            text: "Time"
            checked: midiRouteInput.ignoreTypesMidiTime
            onToggled:{
                midiRouteInput.ignoreTypesMidiTime = checked
            }
        }
        CoreCheckBox {
            id: ignoreTypesMidiSense
            text: "Sence"
            checked: midiRouteInput.ignoreTypesMidiSense
            onToggled:{
                midiRouteInput.ignoreTypesMidiSense = checked
            }
        }
    }
    GroupBox {

        Layout.margins:  Constants.font.pixelSize
        Layout.fillWidth: true
        ColumnLayout {
            anchors.left: parent.left
            anchors.right: parent.right
            CoreLabel {
                text: "<h2>Clock</h2>"
            }
            RowLayout {
                CoreLabel {
                    text: "Time signature from SPP"
                }
                CoreTextField {
                    id: midiRouteClockFromSppPos
                    text: midiRouteInput.midiRouteClockFromSppPos
                    onTextEdited: {
                        midiRouteInput.midiRouteClockFromSppPos = text
                    }
                }
            }
            RowLayout {
                CoreLabel {
                    text: "Upper numeral"
                }
                CoreTextField {
                    id: midiRouteClockTimeSig
                    text: midiRouteInput.midiRouteClockTimeSig
                    onTextEdited: {
                        midiRouteInput.midiRouteClockTimeSig = text
                    }
                }
                CoreLabel {
                    text: "Lower numeral"
                }
                CoreTextField {
                    id: midiRouteClockTimeSigDivBy
                    text: midiRouteInput.midiRouteClockTimeSigDivBy
                    onTextEdited: {
                        midiRouteInput.midiRouteClockTimeSigDivBy = text
                    }
                }
            }
            InPortsSettingsProperate {
                id: inPortsSettingsProperate
                selectedItems: midiRouteInput.midiRouteClockPropegateInputs
                allItems: ["", ...Constants.balData.midiClientConnection.userDataConfig.connectedOutPorts]
                onSelectedItemsModified: ()=>{
                                   midiRouteInput.midiRouteClockPropegateInputs = inPortsSettingsProperate.selectedItems
                                         }
            }

        }
    }

    InPortsSettings14Bit {
        Layout.margins:  Constants.font.pixelSize
        id: inPortsSettings14Bit
        selectedItems: midiRouteInput.midiRouteInputCc14bit
        onSelectedItemsModified: ()=>{
                                     let itms = []
                                     inPortsSettings14Bit.selectedItems.forEach(
                                                 (element) => {
                                                     itms.push({channel: element.channel, cc: element.cc})
                                                 }
                                                 );

                                     midiRouteInput.clear14BitCc();

                                     itms.forEach(
                                                 (element) => {
                                                     midiRouteInput.add14BitCc(element.channel, element.cc)
                                                 }
                                                 );
                                 }
    }
}
