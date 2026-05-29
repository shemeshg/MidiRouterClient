import QtQuick
import QtQuick.Controls
import Design
import Core
import QtQuick.Layouts
import UiComp

CoreTextField {
    id: textFieldWithDialogId

    property string textFieldText: ""
    signal setTextFieldText(string s);
    property var extractedTags: []

    
    TagsEditorDialog {
        id: tagsEditorDialog
    }
    text: textFieldText
    onTextEdited: ()=>{
                      setTextFieldText(text)
                  }


    ContextMenu.menu: Menu {
        MenuSeparator {}
        MenuItem {
            text: "Tags"
            onTriggered: {
                tagsEditorDialog.open();
            }
        }
        MenuSeparator {}
    }


}
