import QtQuick
import Design
import Core
import QtQuick.Layouts
import UiComp

ColumnLayout{
        id: properateInputsId
        property var selectedItems: []
        property var allItems: []
        signal selectedItemsModified()

        RowLayout {
            CoreLabel {
                text: "Propagate Inputes"
            }
            CoreComboBox {
                id: comboId
                model:  properateInputsId.allItems.filter(item => !properateInputsId.selectedItems.includes(item));

                Layout.fillWidth: true
            }
            UiBtnAdd {
                onClicked: {
                    if (comboId.currentText ){
                        properateInputsId.selectedItems.push(comboId.currentText)
                        properateInputsId.selectedItems = [...properateInputsId.selectedItems]
                        selectedItemsModified()
                    }
                }
            }
        }
        Repeater {
            model: properateInputsId.selectedItems
            RowLayout {
                CoreLabel {
                    text: modelData
                }
                UiBtnDel {
                    onClicked: {
                        properateInputsId.selectedItems = properateInputsId.selectedItems.filter(item => item !== modelData);
                        properateInputsId.selectedItemsModified()
                    }
                }
            }
        }
    }
