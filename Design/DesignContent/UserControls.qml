import QtQuick
import Design
import Core
import QtQuick.Layouts
import QtQuick.Controls


ColumnLayout {            
    Layout.fillWidth: true


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
                }
                CoreButton {
                    id: editDropdownsId
                    text: "Dropdowns"
                    hooverText: "Map CC/Program number to meaningfull name"
                    autoExclusive: true
                    checkable: true
                    checked: false
                }
            }
        }
    }
    Loader {
        id: loaderId
        Layout.fillWidth: true
    }
    Component {
        id: controls
        ColumnLayout {
            CoreLabel {
                text:  "User Controls: " + JSON.stringify(Constants.balData.midiClientConnection.userDataConfig.activePreset.userControls)
            }
        }
    }
    Component {
        id: dropdowns
        ColumnLayout {
            CoreLabel {
                text: "Dropdowns"
            }
            CoreButton {
                text: "add"
                onClicked: {
                    Constants.balData.midiClientConnection.userDataConfig.addDropdownList()
                }
            }

            Repeater {
                Layout.fillWidth: true
                model: Constants.balData.midiClientConnection.userDataConfig.dropdownlists

                ColumnLayout {
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
                        CoreButton {
                            text: "del"
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
    }
    states: [
        State {
            name: "Controls"
            when: editControlsId.checked
            PropertyChanges { target: loaderId; sourceComponent: controls }
        },
        State {
            name: "Dropdowns"
            when: editDropdownsId.checked
            PropertyChanges { target: loaderId; sourceComponent: dropdowns }
        }
    ]





}
