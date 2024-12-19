import QtQuick
import Design
import Core
import QtQuick.Layouts


ColumnLayout {            
    Layout.fillWidth: true
    CoreLabel {
        text:  "User Controls: " + JSON.stringify(Constants.balData.midiClientConnection.userDataConfig.activePreset.userControls)
    }

    CoreButton {
        text: "Edit dropdowns"
        onClicked: editDropDowns.visible = !editDropDowns.visible
    }

    ColumnLayout {
        id: editDropDowns
        visible: false
        Repeater {
            Layout.fillWidth: true
            model: Constants.balData.midiClientConnection.userDataConfig.dropdownlists

            RowLayout {                
                CoreLabel {

                    text:   modelData.name // qmllint disable
                }
                CoreTextArea {
                    text:  modelData.data // qmllint disable
                }
            }
        }
    }

}
