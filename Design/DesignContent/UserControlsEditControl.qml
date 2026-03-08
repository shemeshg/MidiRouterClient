import QtQuick
import Design
import Core
import QtQuick.Layouts
import QtQuick.Controls
import UiComp

ColumnLayout {  
    property var control: controlLoaderId.editControlObj


    signal back();



    GroupBox {
        Layout.margins:  Constants.font.pixelSize
        Layout.fillWidth: true

        RowLayout {
            anchors.left: parent.left
            anchors.right: parent.right

            UiBtnBack {
                onClicked: {
                    isSubForm = false;
                    back();
                }
            }
            Item {
                Layout.fillWidth: true
            }
            CoreLabel {
                text: control.description
            }
            Item {
                Layout.fillWidth: true
            }
            CoreLabel {
                text: "Edit user control"
            }
        }
    }





    ColumnLayout {

        Layout.margins:  Constants.font.pixelSize
        CoreSwitch {
            text: "Send on preset change"
            checked: control.isSendOnPresetChange
            onToggled: {
                control.isSendOnPresetChange = checked;
            }
        }
        RowLayout {
            CoreLabel {
                text: "Description"
            }
            CoreTextField {
                text: control.description
                Layout.fillWidth: true
                onTextEdited: ()=>{
                                  control.description = text
                              }
            }
        }

        RowLayout {
            CoreLabel {
                text: "Port name"
            }
            ComboBoxOutport {
                id: portName
                Layout.fillWidth: true
                cmbVal: control.outputPortnName
                onActivated: {
                    control.outputPortnName = currentValue
                }
            }
        }
        RowLayout {

            CoreLabel {
                text: "Event type"
            }
            CoreComboBox {
                id: eventTypeId
                Layout.fillWidth: true
                textRole: "text"
                valueRole: "value"
                model: [
                    {value: 0, text: "CC"},
                    {value: 1, text: "Program Change"},
                    {value: 2, text: "NRPN"}
                ]
                Component.onCompleted: {
                    currentIndex = control.eventType
                }

                onActivated: {
                    control.eventType = currentIndex
                }
            }
        }

        RowLayout {
            CoreLabel {
                text: "Channel"
            }
            CoreTextField {
                text: control.channelId
                Layout.fillWidth: true
                onTextEdited: ()=>{
                                  control.channelId = Number(text)
                              }
            }
        }
        RowLayout {
            visible: eventTypeId.currentIndex === 0
            CoreLabel {
                text: "CC Number"
            }
            CoreTextField {
                text: control.ccId
                Layout.fillWidth: true
                onTextEdited: ()=>{
                                  control.ccId = Number(text)
                              }
            }
        }

        RowLayout {
            visible: eventTypeId.currentIndex === 2
            CoreLabel {
                text: "NRPN Control (14bit)"
            }
            CoreTextField {
                text: control.nrpnControl
                Layout.fillWidth: true
                onTextEdited: ()=>{
                                  control.nrpnControl = Number(text)
                              }
            }
        }
    }

    GroupBox {
        Layout.margins:  Constants.font.pixelSize
        Layout.fillWidth: true
        ColumnLayout {
            anchors.left: parent.left
            anchors.right: parent.right

            RowLayout {
                CoreLabel {
                    text: "Min.Val"
                }
                CoreTextField {
                    text: control.minVal
                    Layout.fillWidth: true
                    onTextEdited: ()=>{
                                      control.minVal = Number(text)
                                  }
                }
            }
            RowLayout {
                CoreLabel {
                    text: "Max.Val"
                }
                CoreTextField {
                    text: control.maxVal
                    Layout.fillWidth: true
                    onTextEdited: ()=>{
                                      control.maxVal = Number(text)
                                  }
                }
            }
            CoreSwitch {
                text: "64 +/- mode"
                checked: control.is64Mode
                onToggled: {
                    control.is64Mode = checked;
                }
            }
        }
    }



    RowLayout {
        Layout.margins:  Constants.font.pixelSize
        CoreSwitch {
            text: "Show dropdown"
            checked: control.isShowDropdown
            onToggled: {
                control.isShowDropdown = checked;
            }
        }
        RowLayout {
            visible: control.isShowDropdown
            CoreLabel {
                text: "Dropdown"
            }
            CoreComboBox {
                id: ddCmbCtrl
                Layout.fillWidth: true
                textRole: "text"
                valueRole: "value"
                model: [{value: -1, name: ""}, ...Constants.balData.midiClientConnection.
                    userDataConfig.dropdownlists.map((item, index) => ({
                             value: item.uuid,
                             text: item.name
                   }))]
                Component.onCompleted: {
                    currentIndex = model.findIndex(item => item.value === control.dropdownListUuid);
                }

                onActivated: {
                    control.dropdownListUuid = currentValue
                }

            }
            UiBtnAdd {
                visible: control.dropdownListUuid === "-1"
                onClicked: {
                    Constants.balData.midiClientConnection.userDataConfig.addDropdownList("new list","","")
                    ddCmbCtrl.currentIndex = ddCmbCtrl.model.length - 1
                    ddCmbCtrl.activated(true)

                }
            }
        }
    }
    function findDropdownByUuid(uuid) {
        const list = Constants.balData.midiClientConnection.userDataConfig.dropdownlists

        for (let i = 0; i < list.length; i++) {
            if (list[i].uuid === uuid) {
                return list[i]     // return the object
            }
        }

        return null
    }


    Loader {
        id: loaderDropDownEdit
        Layout.fillWidth: true
        active: control.isShowDropdown && findDropdownByUuid(control.dropdownListUuid)
        sourceComponent: Component {
            ColumnLayout {

                property var currentDd: findDropdownByUuid(control.dropdownListUuid)
                RowLayout {
                    CoreLabel { text: "name:" }
                    CoreTextField {
                        text:  currentDd.name
                        Layout.fillWidth: true
                        onTextEdited: ()=>{
                                          currentDd.name = text
                                          ddCmbCtrl.displayText = text
                        }
                    }
                }
                CoreTextArea {
                    text:  currentDd.data
                    Layout.fillWidth: true
                    onTextEdited: ()=>{
                        currentDd.data = text
                    }
                }

            }

        }
    }



}
