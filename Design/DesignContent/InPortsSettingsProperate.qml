import QtQuick
import Design
import Core
import QtQuick.Layouts

ColumnLayout{
        id: properateInputsId
        property var selectedItems: []
        property var allItems: []

        RowLayout {
            CoreLabel {
                text: "Propagate Inputes"
            }
            CoreComboBox {
                id: comboId
                model:  properateInputsId.allItems.filter(item => !properateInputsId.selectedItems.includes(item));

                Layout.fillWidth: true
            }
            CoreButton {
                text: "add"
                onClicked: {
                    if (comboId.currentText ){
                        properateInputsId.selectedItems.push(comboId.currentText)
                        properateInputsId.selectedItems = [...properateInputsId.selectedItems]
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
                CoreButton {
                    text: "Del"
                    onClicked: {
                        properateInputsId.selectedItems = properateInputsId.selectedItems.filter(item => item !== modelData);
                    }
                }
            }
        }
    }
