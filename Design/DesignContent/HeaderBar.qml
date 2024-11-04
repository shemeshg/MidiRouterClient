import QtQuick
import Design
import Core
import QtQuick.Layouts
import QtQuick.Controls

RowLayout {


    Item {
        Layout.fillWidth: true
    }
    GroupBox {
        RowLayout {
            CoreButton {
                id: btnLoginId
                text: "Login"
                hooverText: "Login"
                autoExclusive: true
                checkable: true
                checked: true
            }
            CoreButton {
                id: btnVirtualPortsId
                text: "Virtual ports"
                hooverText: "Virtual ports"
                autoExclusive: true
                checkable: true
                checked: false
            }
            CoreButton {
                id: btnPresetsId
                text: "Presets"
                hooverText: "Presets"
                autoExclusive: true
                checkable: true
                checked: false
            }
            CoreButton {
                id: btnUserControlsId
                text: "User controls"
                hooverText: "User controls"
                autoExclusive: true
                checkable: true
                checked: false
            }
        }
    }
    Item {
        Layout.fillWidth: true
    }

    states: [
        State {
            name: "Login"
            when: btnLoginId.checked
        },
        State {
            name: "VirtualPorts"
            when: btnVirtualPortsId.checked
        },
        State {
            name: "Presets"
            when: btnPresetsId.checked
        },
        State {
            name: "UserControls"
            when: btnUserControlsId.checked
        }
    ]

}
