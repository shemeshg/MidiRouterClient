import QtQuick
import Design
import Core
import QtQuick.Layouts

ColumnLayout {
    property var midiRouteInput: Constants.balData.midiClientConnection.userDataConfig.activePreset.getInputOrCreateByName(inPortsLoaderId.inPortName)
    CoreButton {
        text: "back"
        onClicked: {
            inPortsId.state = "InPortsList";
        }
    }    
    RowLayout {
        CoreLabel {
            text: "Routes InPort: " + midiRouteInput.midiInputName
        }
    }
}
