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
            text: "Sysex"
            checked: midiRouteInput.ignoreTypesMidiSysex
        }
        CoreCheckBox {
            text: "Time"
            checked: midiRouteInput.ignoreTypesMidiTime
        }
        CoreCheckBox {
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
            text: midiRouteInput.midiRouteClockFromSppPos
        }
    }
    RowLayout {
        CoreLabel {
            text: "Upper numeral"
        }
        CoreTextField {
            text: midiRouteInput.midiRouteClockTimeSig
        }
        CoreLabel {
            text: "Lower numeral"
        }
        CoreTextField {
            text: midiRouteInput.midiRouteClockTimeSigDivBy
        }
    }
    RowLayout {
        CoreLabel {
            text: "Propagate Inputes"
        }
        CoreComboBox {
            model: ["", ...Constants.balData.midiClientConnection.userDataConfig.connectedOutPorts]
            Layout.fillWidth: true
            Component.onCompleted: {
                var index = model.indexOf(midiControl.portName);
                if (index !== -1) {
                    currentIndex = index;
                }
            }
        }
        CoreButton {
            text: "add"
        }
    }
    CoreLabel {
        text: JSON.stringify(midiRouteInput.midiRouteClockPropegateInputs)
    }
}
