import QtQuick
import Core
import QtQuick.Layouts
import QtQuick.Controls
import Design

RowLayout {
    function selectDefaultItem(isConnected){
        if (isConnected){            
            if (Constants.balData.defaultHeaderTabSelected === "Login"){
                btnLoginId.click();
            } else if (Constants.balData.defaultHeaderTabSelected === "VirtualPorts"){
                btnVirtualPortsId.click();
            } else if (Constants.balData.defaultHeaderTabSelected === "Presets"){
                btnPresetsId.click();
            } else if (Constants.balData.defaultHeaderTabSelected === "UserControls"){
                btnUserControlsId.click();
            } else if (Constants.balData.defaultHeaderTabSelected === "InPorts"){
                btnInPortsId.click();
            } else
            {
                btnInPortsId.click();
            }


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
                hooverText: "<b>⌘1</b> Login"
                autoExclusive: true
                checkable: true
                checked: true
                isAnimation: false
                Shortcut {
                    enabled: btnLoginId.visible && btnLoginId.enabled
                    sequences: ["Ctrl+1"]
                    onActivated: btnLoginId.click()
                }
            }
            CoreButton {
                id: btnVirtualPortsId
                text: "Virtual ports"
                hooverText: "<b>⌘2</b> Virtual ports"
                autoExclusive: true
                checkable: true
                checked: false
                visible: Qt.platform.os !== "windows"
                isAnimation: false
                Shortcut {
                    enabled: btnVirtualPortsId.visible && btnVirtualPortsId.enabled
                    sequences: ["Ctrl+2"]
                    onActivated: btnVirtualPortsId.click()
                }
            }
            CoreButton {
                id: btnPresetsId
                text: "Presets"
                hooverText: "<b>⌘3</b> Presets"
                autoExclusive: true
                checkable: true
                checked: false
                isAnimation: false
                Shortcut {
                    enabled: btnPresetsId.visible && btnPresetsId.enabled
                    sequences: ["Ctrl+3"]
                    onActivated: btnPresetsId.click()
                }
            }
            CoreButton {
                id: btnUserControlsId
                text: "User controls"
                hooverText: "<b>⌘4</b> User controls"
                autoExclusive: true
                checkable: true
                checked: false
                isAnimation: false
                Shortcut {
                    enabled: btnUserControlsId.visible && btnUserControlsId.enabled
                    sequences: ["Ctrl+4"]
                    onActivated: btnUserControlsId.click()
                }
            }
            CoreButton {
                id: btnInPortsId
                text: "In ports"
                hooverText: "<b>⌘5</b> In ports"
                autoExclusive: true
                checkable: true
                checked: false
                isAnimation: false
                Shortcut {
                    enabled: btnInPortsId.visible && btnInPortsId.enabled
                    sequences: ["Ctrl+5"]
                    onActivated: btnInPortsId.click()
                }
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
