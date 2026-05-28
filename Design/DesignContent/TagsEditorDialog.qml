import QtQuick
import QtQuick.Controls
import Design
import Core
import QtQuick.Layouts
import UiComp

Dialog {
    
    id: tagsEditorDialog
    
    popupType: Popup.Window
    implicitWidth:  Constants.balData.width * 0.75
    implicitHeight: Constants.balData.height * 0.75
    standardButtons: Dialog.Ok
    
    modal: true
    ColumnLayout {
        width: parent.width
        
        
        CoreLabel {
            text: textFieldText
        }
        RowLayout {
            Layout.margins: Constants.font.pixelSize
            CoreTextField {
                id: newTagName
                placeholderText: "Type new tag name"
                Layout.fillWidth: true
                focus: true
            }
            CoreButton {
                text: "Add tag"
                onClicked: {
                    let tag = newTagName.text.trim().replace(/^:+/, "")
                    tag = tag.replace(/ /g, "_")
                    if (textFieldText.includes(tag) ){return}
                    setTextFieldText(textFieldText.trim()  + " :" + tag )
                    newTagName.text = ""
                }
            }
        }
        Repeater {
            id: innerRepeaterId
            
            model:  extractedTags
            
            CoreCheckBox {
                Layout.leftMargin:  Constants.font.pixelSize
                text: modelData
                checked: textFieldText.includes(modelData )
                onToggled: ()=>{
                               if (checked) {
                                   setTextFieldText(
                                       textFieldText.trim() + " " + modelData
                                       )
                               } else {
                                   setTextFieldText(
                                       textFieldText.
                                       replace(
                                           new RegExp(modelData, "g")
                                           ,"").trim()
                                       )
                               }
                           }
            }
        }
        
    }
}
