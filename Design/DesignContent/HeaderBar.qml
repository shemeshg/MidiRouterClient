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
        }
    ]

}
