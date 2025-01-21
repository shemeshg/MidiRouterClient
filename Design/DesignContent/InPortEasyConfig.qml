import QtQuick
import Design
import Core
import QtQuick.Layouts
import QtQuick.Controls

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
            text: "Easy config InPort: " + midiRouteInput.midiInputName
        }
    }

    CoreLabel {
        text: "keyboardSplits: " + JSON.stringify(midiRouteInput.easyConfig.keyboardSplits)
    }

    CoreLabel {
        text: "zoneNames: " + JSON.stringify(midiRouteInput.easyConfig.keyboardSplits)
    }

    ComboSilder {
        val: 60
        cmbModel: midiRouteInput.easyConfig.getComboNoesNamesandNumber()
    }


}
