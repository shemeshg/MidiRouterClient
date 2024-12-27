import QtQuick
import Design
import Core
import QtQuick.Layouts

ColumnLayout {
    property var midiRouteInput: Constants.balData.midiClientConnection.userDataConfig.activePreset.getInputOrCreateByName(inPortsLoaderId.inPortName)
    RowLayout {
        CoreLabel {
            text: "Settings InPort: " + midiRouteInput.midiInputName
        }
    }
    CoreButton {
        text: "back"
        onClicked: {
            inPortsId.state = "InPortsList";
        }
    }
}
