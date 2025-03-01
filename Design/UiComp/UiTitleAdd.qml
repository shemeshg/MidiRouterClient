import Core
import QtQuick.Layouts

ColumnLayout {
    id: uiTitleAddId
    property string title: ""
    property string inputText: ""
    signal clicked(message: string)
    function setInputText(s){
        inTextId.text = s
    }

    CoreLabel {
        text: `<h2>${title}</h2>`
    }
    RowLayout {
        CoreTextField {
            id: inTextId
            text: inputText
            Layout.fillWidth: true
        }
        CoreButton {
            text: "add"
            onClicked: {
                uiTitleAddId.clicked(inTextId.text)
            }
        }
    }
}
