/*[[[cog
import cog

filename = "TextFieldWithTagsDialog.qml"

with open(filename, "r", encoding="utf-8") as f:
    content = f.read()

# Replace only the first occurrence
updated = content.replace("CoreTextField", "CoreTextArea", 1)

cog.outl(updated)
]]]*/
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

//[[[end]]]


