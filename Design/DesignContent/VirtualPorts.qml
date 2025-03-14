import Design
import Core
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick
import UiComp

Column {
    ColumnLayout {
        width: parent.width
        id: scrollerWidthId
        Layout.fillWidth: true
    }
    ScrollView {
        contentHeight: virtualPorts.height
        contentWidth: virtualPorts.width
        width: parent.width
        height: parent.height

        ColumnLayout {
            id: virtualPorts
            width: scrollerWidthId.width - 30
            Layout.fillWidth: true



            UiTitleAdd {
                Layout.margins:  Constants.font.pixelSize
                title:"Virtual ports"
                inputText: ""
                onClicked: (txt)=>{
                               if (txt && Constants.balData.midiClientConnection.
                                   userDataConfig.virtualInPorts.indexOf(txt) === -1){

                                   Constants.balData.midiClientConnection.userDataConfig.addVirtualPort(txt)
                                   setInputText("")
                               }
                           }
            }


            Repeater {
                model: Constants.balData.midiClientConnection.userDataConfig.virtualInPorts
                RowLayout {
                    Layout.leftMargin:  Constants.font.pixelSize
                    Layout.rightMargin:  Constants.font.pixelSize
                    CoreLabel {
                        text: modelData
                    }
                    UiBtnDel {
                        onClicked: {
                            Constants.balData.midiClientConnection.userDataConfig.delVirtualPort(index)
                        }
                    }
                }
            }

        }
    }
}
