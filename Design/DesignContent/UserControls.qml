import QtQuick
import Design
import Core
import QtQuick.Layouts
import QtQuick.Controls

ColumnLayout {            
            Layout.fillWidth: true
            CoreLabel {
                text: "User control dropdowns"
            }



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
