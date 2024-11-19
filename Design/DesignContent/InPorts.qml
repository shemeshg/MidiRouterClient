import QtQuick
import Design
import Core
import QtQuick.Layouts
import QtQuick.Controls

ColumnLayout {
    CoreLabel {
        text: "In ports"
    }
    CoreButton{
        onClicked: {
            console.log(
            JSON.stringify(
            Constants.balData.midiClientConnection.userDataConfig)
            )

            dummy.text =             JSON.stringify(
                        Constants.balData.midiClientConnection.userDataConfig.
                            midiRoutePresets[0].midiRouteInputs
                            )
        }
    }

    CoreTextArea {
        id: dummy
        wrapMode: Text.WordWrap
    }
}
