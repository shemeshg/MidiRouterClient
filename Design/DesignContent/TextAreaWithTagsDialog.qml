import QtQuick
import QtQuick.Controls
import Design
import Core
import QtQuick.Layouts
import UiComp

CoreTextArea {
    id: textFieldWithDialogId

    property string textFieldText: ""
    signal setTextFieldText(string s);
    property var extractedTags: []

    Component {
        id: separatorComponent
        MenuSeparator {}
    }
    Component {
        id: tagsPopupMenuItemComponent
        MenuItem {
            text: "Tags"
            onTriggered: {
                tagsEditorDialog.open();
            }
        }
    }

    TagsEditorDialog {
        id: tagsEditorDialog
    }
    text: textFieldText
    onTextEdited: ()=>{
                      setTextFieldText(text)
                  }
    Component.onCompleted: {


        textFieldWithDialogId.ContextMenu.menu.addItem(separatorComponent.createObject())
        textFieldWithDialogId.ContextMenu.menu.addItem(tagsPopupMenuItemComponent.createObject())

    }
}
