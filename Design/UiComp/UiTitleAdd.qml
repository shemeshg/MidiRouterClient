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


    CoreGroupBox {
        Layout.fillWidth: true
        ColumnLayout {
            anchors.left: parent.left
            anchors.right: parent.right
            Layout.fillWidth: true
            UiTitle {
                title: uiTitleAddId.title
            }

            RowLayout {
                Layout.fillWidth: true
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
    }
}
