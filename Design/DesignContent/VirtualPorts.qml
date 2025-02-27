import Design
import Core
import QtQuick.Layouts
import QtQuick

ColumnLayout {
    id: virtualPorts
    Layout.fillWidth: true
    CoreLabel {
        text: "<h1>Virtual ports</h1>"
    }

    CoreLabel {
        text: "virtual ports "
    }
    RowLayout {
        CoreTextField {
            id: newPortId
            text: ""
            Layout.fillWidth: true
        }
        CoreButton {
            text: "add"
            onClicked: {
                if (newPortId.text && Constants.balData.midiClientConnection.
                        userDataConfig.virtualInPorts.indexOf(newPortId.text) === -1){

                    Constants.balData.midiClientConnection.userDataConfig.addVirtualPort(newPortId.text)
                }
            }
        }
    }
    Repeater {
        model: Constants.balData.midiClientConnection.userDataConfig.virtualInPorts
        RowLayout {
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
