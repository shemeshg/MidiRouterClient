import QtQuick
import Design
import Core
import QtQuick.Layouts

ColumnLayout {
       RowLayout {
           CoreLabel {
               text: "Easy Config InPort: " + inPortsLoaderId.inPortName
           }
       }
       CoreButton {
        text: "back"
        onClicked: {
            inPortsId.state = "InPortsList"
            }
       }
    }
