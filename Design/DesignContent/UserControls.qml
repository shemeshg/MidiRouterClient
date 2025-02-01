import QtQuick
import Design
import Core
import QtQuick.Layouts
import QtQuick.Controls


ColumnLayout {            
    Layout.fillWidth: true
    id: userControlsId

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
                    onClicked: {

                        loaderId.sourceComponent = controls
                    }
                }
                CoreButton {
                    id: editDropdownsId
                    text: "Dropdowns"
                    hooverText: "Map CC/Program number to meaningfull name"
                    autoExclusive: true
                    checkable: true
                    checked: false
                    onClicked: {
                        state = "Dropdowns"
                        loaderId.sourceComponent = dropdowns
                    }
                }
            }
        }
    }
    Loader {
        id: loaderId        
        Layout.fillWidth: true
        sourceComponent: controls
    }
    Component {
        id: controls
        UserControlsList {
            activePreset: Constants.balData.midiClientConnection.userDataConfig.activePreset
            onEditControl: (v)=>{
                        loaderId.sourceComponent = userControls;
                        loaderId.item.control  = v;
                    }
        }
    }
    Component {
        id: dropdowns
        UserControlsDropdowns {
        }
    }

    Component {
        id: userControls
        UserControlsEditControl {
            onBack: {
                loaderId.sourceComponent = controls
            }
        }
    }







}
