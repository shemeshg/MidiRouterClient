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


    RowLayout {
        CoreLabel {
            text: "Description"
        }
        CoreTextField {
            text: control.description
            Layout.fillWidth: true
            onTextEdited: ()=>{
                             control.description = text
            }
        }
    }

    RowLayout {
        CoreLabel {
            text: "Port name"
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
            id: eventTypeId
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
    RowLayout {
        CoreLabel {
            text: "Min.Val"
        }
        CoreTextField {
            text: control.minVal
            Layout.fillWidth: true
            onTextEdited: ()=>{
                             control.minVal = Number(text)
            }
        }
    }
    RowLayout {
        CoreLabel {
            text: "Max.Val"
        }
        CoreTextField {
            text: control.minVal
            Layout.fillWidth: true
            onTextEdited: ()=>{
                             control.maxVal = Number(text)
            }
        }
    }
    CoreSwitch {
        text: "64 +/- mode"
        checked: control.is64Mode
        onToggled: {
            control.is64Mode = checked;
        }
    }
    RowLayout {
        CoreLabel {
            text: "Channel"
        }
        CoreTextField {
            text: control.channelId
            Layout.fillWidth: true
            onTextEdited: ()=>{
                             control.channelId = Number(text)
            }
        }
    }
    RowLayout {
        CoreLabel {
            text: "CC Number"
        }
        CoreTextField {
            text: control.ccId
            Layout.fillWidth: true
            onTextEdited: ()=>{
                             control.ccId = Number(text)
            }
        }
    }

    RowLayout {
        visible: eventTypeId.currentIndex === 2
        CoreLabel {
            text: "NRPN Control (14bit)"
        }
        CoreTextField {
            text: control.nrpnControl
            Layout.fillWidth: true
            onTextEdited: ()=>{
                             control.nrpnControl = Number(text)
            }
        }
    }
}
