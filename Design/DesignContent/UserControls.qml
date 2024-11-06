import QtQuick
import Design
import Core
import QtQuick.Layouts
import QtQuick.Controls

ColumnLayout {            
    Layout.fillWidth: true


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
                    text:   modelData.name
                }
                CoreTextArea {
                    text:  modelData.data
                }
            }
        }
    }

}
