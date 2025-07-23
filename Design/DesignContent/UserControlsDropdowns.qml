import QtQuick
import Design
import Core
import QtQuick.Layouts
import QtQuick.Controls
import UiComp

ColumnLayout {
    GroupBox {
        Layout.fillWidth: true
        Layout.margins:  Constants.font.pixelSize
        RowLayout {
            anchors.left: parent.left
            anchors.right: parent.right
            UiTitle {
                title: "Dropdowns"
            }
            Item {
                Layout.fillWidth: true
            }
            UiBtnAdd {
                onClicked: {
                    Constants.balData.midiClientConnection.userDataConfig.addDropdownList("new list","","")
                }
            }
        }
    }

    Repeater {
        Layout.fillWidth: true
        model: Constants.balData.midiClientConnection.userDataConfig.dropdownlists

        ColumnLayout {
            Layout.leftMargin:  Constants.font.pixelSize
            Layout.rightMargin:  Constants.font.pixelSize
            RowLayout {

                CoreLabel {
                    text: editDropdown.visible ? "⏷ " : "⏵ "
                    MouseArea {
                        anchors.fill: parent
                        cursorShape: Qt.PointingHandCursor
                        onClicked: editDropdown.visible = !editDropdown.visible
                    }
                }
                CoreLabel {
                    text: "name: "
                    MouseArea {
                        anchors.fill: parent
                        cursorShape: Qt.PointingHandCursor
                        onClicked: editDropdown.visible = !editDropdown.visible
                    }
                }

                CoreTextField {
                    text:   modelData.name // qmllint disable
                    onTextEdited: ()=>{
                                      modelData.name = text
                                  }
                    Layout.fillWidth: true
                }
                UiBtnDel {
                    onClicked: {
                        Constants.balData.midiClientConnection.userDataConfig.delDropdownList(index)
                    }
                }

            }
            ColumnLayout {
                id: editDropdown
                visible: false
                CoreLabel {
                    text: "Items per line: "
                }
                CoreTextArea {
                    text:  modelData.data
                    Layout.fillWidth: true
                    property bool processing: true
                    onTextChanged: {
                        if (!processing) {
                            processing = true
                            modelData.data = text;
                        }
                    }

                    Keys.onPressed: {
                        processing = false
                    }
                }
            }
        }
    }
}
