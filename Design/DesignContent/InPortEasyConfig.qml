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
            midiRouteInput.easyConfig.emitKeyboardSplitsChanged()
            inPortsId.state = "InPortsList";
        }
    }
    RowLayout {
        CoreLabel {
            text: "Easy config InPort: " + midiRouteInput.midiInputName
        }
    }

    CoreLabel {
        text: "<h1>Keyboard splits</h1>"
    }


    CoreButton {
        text: "Add"
        onClicked: {
            midiRouteInput.easyConfig.appendSplit(60)
        }
    }

    Repeater {
        model: [...midiRouteInput.easyConfig.keyboardSplits]
        RowLayout {
            ComboSilder {
                val: modelData

                cmbModel: midiRouteInput.easyConfig.getComboNoesNamesandNumber()
                onDel: {
                    midiRouteInput.easyConfig.delSplit(index)
                }
                name: midiRouteInput.easyConfig.zoneNames[index + 1]
                onSetVal: (i)=>{

                            midiRouteInput.easyConfig.setSplitNoEmmit(index,i)
                        }
                onSetName: (s)=>{
                               midiRouteInput.easyConfig.zoneNames[index + 1] = s;
                         }
            }
        }
    }

    CoreLabel {
        text: "<h1>Routes</h1>"
    }
}
