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

    CoreTextArea {
        id: dummy
        wrapMode: Text.WordWrap
    }
}
