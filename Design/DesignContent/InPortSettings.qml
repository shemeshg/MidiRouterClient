import QtQuick
import Design
import Core
import QtQuick.Layouts

ColumnLayout {
       RowLayout {
           CoreLabel {
               text: "Settings InPort: " + inPortsLoaderId.inPortName
           }
       }
       CoreButton {
        text: "back"
        onClicked: {
            inPortsId.state = "InPortsList"
            }
       }
    }
