import QtQuick
import Design
import Core
import QtQuick.Layouts
import QtQuick.Controls


ColumnLayout {  
    property var control: loaderId.editControlObj


    signal back();
    CoreButton {
        text: "back"
        onClicked: {
            back();
        }
    }

    CoreLabel {
        text: "editControl"
    }

    RowLayout {
        CoreLabel {
            text: "portName"
        }
        CoreComboBox {
            id: portName
            Layout.fillWidth: true
            model: ["", ...Constants.balData.midiClientConnection.userDataConfig.connectedOutPorts]

            Component.onCompleted: {
                var index = model.indexOf(control.outputPortnName);
                if (index !== -1) {
                    currentIndex = index;
                }
            }
            onActivated: {
                control.outputPortnName = currentText
            }
        }
    }
    RowLayout {
        CoreLabel {
            text: "Event type"
        }
        CoreComboBox {
            editable: true
            textRole: "text"
            valueRole: "value"
            model: [
                {value: 0, text: "CC"},
                {value: 1, text: "Program Change"},
                {value: 2, text: "NRPN"}
            ]
            Component.onCompleted: {
                currentIndex = control.eventType
            }

            onActivated: {
                control.eventType = currentIndex
            }
        }


    }

}
