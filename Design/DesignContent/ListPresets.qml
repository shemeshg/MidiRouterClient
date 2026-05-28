import QtQuick
import QtQuick.Controls
import Design
import Core
import QtQuick.Layouts
import UiComp

ColumnLayout {

    GroupBox {
        Layout.margins:  Constants.font.pixelSize
        Layout.fillWidth: true
        RowLayout {

            anchors.left: parent.left
            anchors.right: parent.right
            UiTitle {
                title: "Presets"


            }
            Item {
                Layout.fillWidth: true
            }
            UiBtnAdd {
                onClicked: {
                    Constants.balData.midiClientConnection.userDataConfig.addPreset();
                }
                enabled: regexFilter.isEmpty()
            }
        }
    }


    RegexFilter {
        id: regexFilter

        regexPlaceholderText: "RegEx filter by description ex. tag1|tag2 (⏎ - select 1st)"
        extractTagsAry: Constants.balData.midiClientConnection.userDataConfig.midiRoutePresets
        extractTagsField: "name"
        onControlAccepted: ()=>{
            for (let i = 0; i < presetRepeater.count; i++) {
                let item = presetRepeater.itemAt(i)
                if (item && item.visible) {
                    item.selectPreset()
                    break
                }
            }
        }
    }

    Repeater {
        id: presetRepeater
        Layout.fillWidth: true
        model: Constants.balData.midiClientConnection.userDataConfig.midiRoutePresets

        RowLayout {
            function selectPreset(){
                Constants.balData.midiClientConnection.userDataConfig.setActivePreset(index, true);
                Constants.balData.applyConfig(() => {
                });
            }

            Layout.leftMargin:  Constants.font.pixelSize
            Layout.rightMargin:  Constants.font.pixelSize
            visible: regexFilter.testFilterByDescription(modelData.name)
            CoreButton {
                hooverText: "select"
                icon.name: "select"
                icon.source: Qt.resolvedUrl("icons/ink_selection_24dp_E3E3E3_FILL0_wght400_GRAD0_opsz24.svg")
                icon.color: CoreSystemPalette.buttonText
                palette.buttonText: CoreSystemPalette.buttonText


                visible: index !== Constants.balData.midiClientConnection.userDataConfig.activePresetID
                onClicked: {
                    selectPreset();
                }
            }
            CoreSwitch {
                text: ""
                checked: modelData.isEnabled
                onToggled: {
                    modelData.isEnabled = checked;
                    Constants.balData.applyConfig(() => {
                    });
                }
            }

            CoreTextField {
                id: myInput
                Component {
                    id: separatorComponent
                    MenuSeparator {}
                }
                Component {
                    id: tagsPopupMenuItemComponent
                    MenuItem {
                        text: "Tags"
                           onTriggered: {
                               tagsEditorDialog.tagsEditorText = myInput.text

                               tagsEditorDialog.open();
                           }
                    }
                }


                Dialog {

                    id: tagsEditorDialog
                    property string tagsEditorText: ""

                    popupType: Popup.Window
                    height: 100
                    width: 100
                    modal: false
                    ColumnLayout {
                        CoreLabel {
                            text: tagsEditorDialog.tagsEditorText
                        }
                        RowLayout {
                            CoreTextField {
                                id: newTagName
                                placeholderText: "Type new tag name"
                            }
                            CoreButton {
                                text: "Add tag"
                                onClicked: {
                                    let tag = newTagName.text.trim().replace(/^:+/, "")
                                    modelData.name  = modelData.name  + " :" + tag
                                    newTagName.text = ""
                                }
                            }
                        }
                        Repeater {
                            model:  regexFilter.extractedTags()
                            CoreCheckBox {
                                text: modelData
                            }
                        }
                    }
                }
                text: modelData.name
                Layout.fillWidth: true
                onTextEdited: ()=>{
                                 modelData.name = text;
                              }
                Component.onCompleted: {


                        myInput.ContextMenu.menu.addItem(separatorComponent.createObject())
                        myInput.ContextMenu.menu.addItem(tagsPopupMenuItemComponent.createObject())

                }
            }

            UiBtnDel {
                visible: Constants.balData.midiClientConnection.userDataConfig.midiRoutePresets.length > 1 && index !== Constants.balData.midiClientConnection.userDataConfig.activePresetID
                onClicked: {
                    Constants.balData.midiClientConnection.userDataConfig.deletePreset(index);
                }
            }
            UiBtnEdit {
                onClicked: {
                    presetsLoaderId.presetIndex = index;
                    isSubForm = true
                    presets.state = "EditPreset";

                }
            }
            UiBtnUp {
                visible: Constants.balData.midiClientConnection.userDataConfig.midiRoutePresets.length > 1
                onClicked: {
                    Constants.balData.midiClientConnection.userDataConfig.movePreset(index, index - 1);
                }
            }

        }
    }



}
