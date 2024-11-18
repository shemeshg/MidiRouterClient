import QtQuick
import Design
import Core
import QtQuick.Layouts
import QtQuick.Controls

ColumnLayout {
    CoreLabel {
        text: "In ports"
    }
    CoreTextArea {
        text:
            JSON.stringify(
            Constants.balData.midiClientConnection.userDataConfig.
                midiRoutePresets[0].midiRouteInputs
                )
        wrapMode: Text.WordWrap
    }
}
