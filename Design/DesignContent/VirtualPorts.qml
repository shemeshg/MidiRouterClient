import Design
import Core
import QtQuick.Layouts
import QtQuick
import UiComp

ColumnLayout {
    id: virtualPorts
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
            CoreButton {
                text: "del"
                onClicked: {
                    Constants.balData.midiClientConnection.userDataConfig.delVirtualPort(index)
                }
            }
        }
    }

}
