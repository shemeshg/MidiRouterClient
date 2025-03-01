import Core
import QtQuick.Layouts
import UiComp

ColumnLayout {
    id: uiTitleAddId
    property string title: ""
    property string inputText: ""
    signal clicked(message: string)
    function setInputText(s){
        inTextId.text = s
    }
    UiTitle {
        title: uiTitleAddId.title
    }

    RowLayout {
        CoreTextField {
            id: inTextId
            text: inputText
            Layout.fillWidth: true
        }
        UiBtnAdd {
            onClicked: {
                uiTitleAddId.clicked(inTextId.text)
            }
        }
    }
}
