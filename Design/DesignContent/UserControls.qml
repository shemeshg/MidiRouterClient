import QtQuick
import Design
import Core
import QtQuick.Layouts
import QtQuick.Controls

ColumnLayout {            
    Layout.fillWidth: true
    CoreLabel {
        text:  "User Controls: " + JSON.stringify(Constants.balData.midiClientConnection.
                                                  userDataConfig.midiRoutePresets[0].userControls)
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
                    text:   modelData.name
                }
                CoreTextArea {
                    text:  modelData.data
                }
            }
        }
    }

}
