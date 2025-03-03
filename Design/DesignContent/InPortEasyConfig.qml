import QtQuick
import Design
import Core
import QtQuick.Layouts
import QtQuick.Controls
import UiComp

ColumnLayout {
    property var midiRouteInput: Constants.balData.midiClientConnection.userDataConfig.activePreset.getInputOrCreateByName(inPortsLoaderId.inPortName)

    GroupBox {
        Layout.margins:  Constants.font.pixelSize
        Layout.fillWidth: true

        RowLayout {
            anchors.left: parent.left
            anchors.right: parent.right

            UiBtnBack {
                onClicked: {
                    midiRouteInput.easyConfig.emitKeyboardSplitsChanged()
                    isEasyConfigForm = false
                    isSubForm = false
                    inPortsId.state = "InPortsList";
                }
            }
            Item {
                Layout.fillWidth: true
            }
            CoreLabel {
                text: midiRouteInput.midiInputName
            }
            Item {
                Layout.fillWidth: true
            }
            CoreLabel {
                text: "Edit EasyConfig"
            }
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
