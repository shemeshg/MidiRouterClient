import QtQuick
import Core
import QtQuick.Layouts
import QtQuick.Controls
import Design

RowLayout {
    function selectDefaultItem(isConnected){
        if (isConnected){
            btnInPortsId.click();
        } else {
            btnLoginId.click();
        }
    }



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
                visible: Qt.platform.os !== "windows"
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
            CoreButton {
                id: btnInPortsId
                text: "In ports"
                hooverText: "In ports"
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
        },
        State {
            name: "InPorts"
            when: btnInPortsId.checked
        }


    ]

}
