import QtQuick
import Design
import Core
import QtQuick.Layouts
import QtQuick.Controls

ColumnLayout {

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
    }
