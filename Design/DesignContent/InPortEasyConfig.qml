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
            midiRouteInput.easyConfig.emitKeyboardSplitsChanged()
            isEasyConfigForm = false
            isSubForm = false
            inPortsId.state = "InPortsList";
        }
    }

    RowLayout {
        CoreLabel {
            text: "Easy config InPort: " + midiRouteInput.midiInputName
        }
    }

    Loader {
        id: loaderId
        Layout.fillWidth: true
    }
    Component {
        id: inPortEasyConfigSplits
        InPortEasyConfigSplits {
        }
    }

    Component {
        id: inPortEasyConfigRoutes
        InPortEasyConfigRoutes {
        }
    }
    states: [
        State {
            name: "Routes"
            when: easyConfigRoutesId.checked
            PropertyChanges { target: loaderId; sourceComponent: inPortEasyConfigRoutes }
        },
        State {
            name: "Splits"
            when: easyConfigSplitsId.checked
            PropertyChanges { target: loaderId; sourceComponent: inPortEasyConfigSplits }
        }
    ]
}
