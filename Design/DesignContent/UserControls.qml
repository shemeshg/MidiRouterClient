import QtQuick
import Design
import Core
import QtQuick.Layouts
import QtQuick.Controls


ColumnLayout {            
    Layout.fillWidth: true


    RowLayout {
        GroupBox {
            RowLayout {
                CoreButton {
                    id: editControlsId
                    text: "Controls"
                    hooverText: "User controls"
                    autoExclusive: true
                    checkable: true
                    checked: true
                }
                CoreButton {
                    id: editDropdownsId
                    text: "Dropdowns"
                    hooverText: "Map CC/Program number to meaningfull name"
                    autoExclusive: true
                    checkable: true
                    checked: false
                }
            }
        }
    }
    Loader {
        id: loaderId
        Layout.fillWidth: true
    }
    Component {
        id: controls
        UserControlsList {
            activePreset: Constants.balData.midiClientConnection.userDataConfig.activePreset
        }
    }
    Component {
        id: dropdowns
        UserControlsDropdowns {
        }
    }
    states: [
        State {
            name: "Controls"
            when: editControlsId.checked
            PropertyChanges { target: loaderId; sourceComponent: controls }
        },
        State {
            name: "Dropdowns"
            when: editDropdownsId.checked
            PropertyChanges { target: loaderId; sourceComponent: dropdowns }
        }
    ]





}
