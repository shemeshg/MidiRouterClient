import QtQuick
import Design
import Core
import QtQuick.Layouts
import QtQuick.Controls
import UiComp

ColumnLayout {

    GroupBox {
        Layout.margins:  Constants.font.pixelSize
        Layout.fillWidth: true

        RowLayout {
            Layout.leftMargin: Constants.font.pixelSize
            Layout.rightMargin: Constants.font.pixelSize
            anchors.left: parent.left
            anchors.right: parent.right
            UiTitle {
                title: "Keyboard splits"
            }
            Item {
                Layout.fillWidth: true
            }
            UiBtnAdd {
                onClicked: {
                    midiRouteInput.easyConfig.appendSplit(60)
                }

            }
        }
    }

    Repeater {
        model: [...midiRouteInput.easyConfig.keyboardSplits]
        RowLayout {
            Layout.leftMargin: Constants.font.pixelSize
            Layout.rightMargin: Constants.font.pixelSize
            ComboSilder {
                val: modelData

                cmbModel: midiRouteInput.easyConfig.getComboNoesNamesAndNumber()
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
