import QtQuick
import Design
import Core
import QtQuick.Layouts
import QtQuick.Controls


ColumnLayout {
            property var activePreset: ({})
            CoreLabel {
                text:  "User Controls: "
            }
            RowLayout {
                CoreButton {
                    text: "Send all"
                    onClicked: {
                        activePreset.sendAllUserControls()
                    }
                }

                CoreButton {
                    text: "Add"
                    onClicked: {
                        activePreset.addUserControl()
                        console.log(
                                    JSON.stringify(activePreset.userControls)
                                    )
                    }
                }
            }
        }
