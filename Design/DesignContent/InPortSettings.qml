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
    InPortsSettingsProperate {
       selectedItems: midiRouteInput.midiRouteClockPropegateInputs
        allItems: ["", ...Constants.balData.midiClientConnection.userDataConfig.connectedOutPorts]
    }

    RowLayout {
        CoreLabel {
            text: "<h2>14Bit CC</h2>"
        }
    }
    RowLayout {
        CoreLabel {
            text: "Channel"
        }
        CoreTextField {
           id: cc14bitChannel
           text: "1"
        }
        CoreLabel {
            text: "CC"
        }
        CoreTextField {
            id: cc14bitCc
            text: "0"
        }
        CoreButton{
            text: "add"
            onClicked: {
                cc14bitErr.text = ""
                if (
                        Number(cc14bitChannel.text) < 1 ||
                        Number(cc14bitChannel.text) > 16 ||
                        Number(cc14bitCc.text) < 0 ||
                        Number(cc14bitCc.text) > 17
                      ) {
                        cc14bitErr.text = "14bit requires Channel 1..16 cc 1..16"
                        return;
                      }
                /* -- add value if not exists
                      if (
                        midiRouteInput.value.cc14bitAry.filter((row) => {
                          return (
                            row.channel === cc14bitChannel.value && row.cc === cc14bitCc.value
                          );
                        }).length > 0
                      ) {
                        return;
                      }
                      midiRouteInput.value.addCc14bitAry(cc14bitChannel.value, cc14bitCc.value);

                      */
            }
        }
    }

    CoreLabel {
        visible: text !==""
        id: cc14bitErr
        text: ""
    }
}
