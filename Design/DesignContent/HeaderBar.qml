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




            ButtonGroup {
                id: navGroup
                exclusive: true
            }
            Shortcut {
                sequences: ["Ctrl+2"]
                onActivated: ()=>{
                                 let buttons = navGroup.buttons
                                 let count = buttons.length
                                 let index = buttons.indexOf(navGroup.checkedButton)

                                 let prev = index
                                 do {
                                     prev = (prev - 1 + count) % count
                                     if (buttons[prev].visible && buttons[prev].enabled) {
                                         buttons[prev].checked = true
                                         return
                                     }
                                 } while (prev !== index)
                             }
            }

            Shortcut {
                sequences: ["Ctrl+1"]
                onActivated: ()=>{
                                 let buttons = navGroup.buttons
                                 let count = buttons.length
                                 let index = buttons.indexOf(navGroup.checkedButton)

                                 let next = index
                                 do {
                                     next = (next + 1) % count
                                     if (buttons[next].visible && buttons[next].enabled) {
                                         buttons[next].checked = true
                                         return
                                     }
                                 } while (next !== index)


                             }
            }

            CoreButton {
                id: btnLoginId
                text: "Login"
                hooverText: "<b>⌘1</b>← <b>⌘2</b>→"
                ButtonGroup.group: navGroup
                checkable: true
                checked: true
                isAnimation: false
            }
            CoreButton {
                id: btnVirtualPortsId
                text: "Virtual ports"
                hooverText: "<b>⌘1</b>← <b>⌘2</b>→"
                ButtonGroup.group: navGroup
                checkable: true
                checked: false
                visible: Qt.platform.os !== "windows"
                isAnimation: false
            }
            CoreButton {
                id: btnPresetsId
                text: "Presets"
                hooverText: "<b>⌘1</b>← <b>⌘2</b>→"
                ButtonGroup.group: navGroup
                checkable: true
                checked: false
                isAnimation: false
            }
            CoreButton {
                id: btnUserControlsId
                text: "User controls"
                hooverText: "<b>⌘1</b>← <b>⌘2</b>→"
                ButtonGroup.group: navGroup
                checkable: true
                checked: false
                isAnimation: false
            }
            CoreButton {
                id: btnInPortsId
                text: "In ports"
                hooverText: "<b>⌘1</b>← <b>⌘2</b>→"
                ButtonGroup.group: navGroup
                checkable: true
                checked: false
                isAnimation: false
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
