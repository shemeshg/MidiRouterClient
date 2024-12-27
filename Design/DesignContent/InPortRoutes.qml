import QtQuick
import Design
import Core
import QtQuick.Layouts

ColumnLayout {
       RowLayout {
           CoreLabel {
               text: "Routes InPort: " + inPortsLoaderId.inPortName
           }
       }
       CoreButton {
        text: "back"
        onClicked: {
            inPortsId.state = "InPortsList"
            }
       }
    }
