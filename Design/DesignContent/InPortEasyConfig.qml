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
            inPortsId.state = "InPortsList";
        }
    }
    RowLayout {
        GroupBox {
            RowLayout {
                CoreButton {
                    id: easyConfigRoutesId
                    text: "Routes"
                    hooverText: "Routes"
                    autoExclusive: true
                    checkable: true
                    checked: true
                }
                CoreButton {
                    id: easyConfigSplitsId
                    text: "Splits"
                    hooverText: "Keyboard Splits"
                    autoExclusive: true
                    checkable: true
                    checked: false
                }
            }
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
