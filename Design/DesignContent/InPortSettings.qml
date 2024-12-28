import QtQuick
import Design
import Core
import QtQuick.Layouts

ColumnLayout {    
    property var midiRouteInput: Constants.balData.midiClientConnection.userDataConfig.activePreset.getInputOrCreateByName(inPortsLoaderId.inPortName)

    CoreButton {
        text: "back"
        onClicked: {
            inPortsId.state = "InPortsList";
        }
    }
    CoreButton {
        text: "save"
        onClicked: {
            midiRouteInput.ignoreTypesMidiSysex  = ignoreTypesMidiSysex.checked
            midiRouteInput.ignoreTypesMidiTime  = ignoreTypesMidiTime.checked
            midiRouteInput.ignoreTypesMidiSense  = ignoreTypesMidiSense.checked

            midiRouteInput.midiRouteClockFromSppPos = midiRouteClockFromSppPos.text
            midiRouteInput.midiRouteClockTimeSig = midiRouteClockTimeSig.text
            midiRouteInput.midiRouteClockTimeSigDivBy = midiRouteClockTimeSigDivBy.text
            midiRouteInput.midiRouteClockPropegateInputs = inPortsSettingsProperate.selectedItems


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

    RowLayout {
        CoreLabel {
            text: "Settings InPort: " + midiRouteInput.midiInputName
        }
    }
    CoreLabel {
        text: "<h2>Ignore Types</h2>"
    }
    RowLayout {
        CoreCheckBox {
            id: ignoreTypesMidiSysex
            text: "Sysex"
            checked: midiRouteInput.ignoreTypesMidiSysex
        }
        CoreCheckBox {
            id: ignoreTypesMidiTime
            text: "Time"
            checked: midiRouteInput.ignoreTypesMidiTime
        }
        CoreCheckBox {
            id: ignoreTypesMidiSense
            text: "Sence"
            checked: midiRouteInput.ignoreTypesMidiSense
        }
    }
    CoreLabel {
        text: "Clock"
    }
    RowLayout {
        CoreLabel {
            text: "Time signature from SPP"
        }
        CoreTextField {
            id: midiRouteClockFromSppPos
            text: midiRouteInput.midiRouteClockFromSppPos
        }
    }
    RowLayout {
        CoreLabel {
            text: "Upper numeral"
        }
        CoreTextField {
            id: midiRouteClockTimeSig
            text: midiRouteInput.midiRouteClockTimeSig
        }
        CoreLabel {
            text: "Lower numeral"
        }
        CoreTextField {
            id: midiRouteClockTimeSigDivBy
            text: midiRouteInput.midiRouteClockTimeSigDivBy
        }
    }
    InPortsSettingsProperate {
        id: inPortsSettingsProperate
        selectedItems: midiRouteInput.midiRouteClockPropegateInputs
        allItems: ["", ...Constants.balData.midiClientConnection.userDataConfig.connectedOutPorts]
    }

    InPortsSettings14Bit {
        id: inPortsSettings14Bit
        selectedItems: midiRouteInput.midiRouteInputCc14bit
    }
}
