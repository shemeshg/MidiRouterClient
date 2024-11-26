import Design
import Core
import QtQuick.Layouts


ColumnLayout {
    id: virtualPorts
    Layout.fillWidth: true
    CoreLabel {
        text: "<h1>Virtual ports</h1>"
    }
    CoreLabel {
        text: "virtual ports " + Constants.balData.midiClientConnection.userDataConfig.virtualInPorts
    }
}
