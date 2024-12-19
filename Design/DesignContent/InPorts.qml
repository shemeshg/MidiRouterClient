import QtQuick
import Design
import Core
import QtQuick.Layouts


ColumnLayout {
    CoreLabel {
        text: "In ports"
    }
    CoreButton{
        onClicked: {
            console.log(
            JSON.stringify(
            Constants.balData.midiClientConnection.userDataConfig.getJson())
            )

            dummy.text =             JSON.stringify(
                        Constants.balData.midiClientConnection.userDataConfig.
                            midiRoutePresets[0].midiRouteInputs
                            )
        }
    }

    CoreLabel {
        text: "<h1>Connected in ports</h1>";
    }

    Repeater {
        model: Constants.balData.midiClientConnection.userDataConfig.connectedInPorts
        RowLayout {
            CoreLabel {
                text: modelData
            }
        }
    }
    CoreTextArea {
        id: dummy
        wrapMode: Text.WordWrap
    }
}
