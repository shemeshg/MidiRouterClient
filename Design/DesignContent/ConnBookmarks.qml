import QtQuick
import Design
import Core
import QtQuick.Layouts
import QtQuick.Controls
import UiComp

ColumnLayout {
    id: connBookmarks
    property var connBookmarksList: []


    function moveItemSplice(arr, from, to) {
        const size = arr.length;
        to = (to + size) % size;


        const [item] = arr.splice(from, 1);
        arr.splice(to, 0, item);
    }


    RowLayout {
        
        CoreLabel {
            leftPadding: Constants.font.pixelSize
            text: "<h3>Conn. bookmarks</h3>"
        }
        Item {
            Layout.fillWidth: true
        }
        UiBtnAdd {
            onClicked: {

                connBookmarksList.push({server: "localhost", port: 9999, name:"new bookmark"})
                connBookmarksListRepeater.model = [...connBookmarksList]
            }
        }
    }
    ColumnLayout {
        Repeater {
            id: connBookmarksListRepeater
            Layout.fillWidth: true
            model: []
            RowLayout {
                Layout.rightMargin: Constants.font.pixelSize
                Layout.leftMargin: Constants.font.pixelSize * 2
                CoreButton {
                    hooverText: "select"
                    icon.name: "select"
                    icon.source: Qt.resolvedUrl("icons/ink_selection_24dp_E3E3E3_FILL0_wght400_GRAD0_opsz24.svg")
                    icon.color: CoreSystemPalette.buttonText
                    palette.buttonText: CoreSystemPalette.buttonText


                    onClicked: {

                        console.log("connected");
                    }
                }
                CoreTextField {
                    text: modelData.server
                    Layout.fillWidth: true
                    onTextEdited: ()=>{
                                    connBookmarksList[index].server = text
                                  }
                }
                CoreTextField {
                    text: modelData.port
                    Layout.fillWidth: true
                    onTextEdited: ()=>{
                                    connBookmarksList[index].port = Number(text)
                                  }
                }
                CoreTextField {
                    text: modelData.name
                    Layout.fillWidth: true
                    onTextEdited: ()=>{
                                    connBookmarksList[index].name = text
                                  }
                }
                UiBtnDel {
                    visible: (connBookmarksList.length > 1 ) ||
                             connBookmarksList.length === 1
                    onClicked: {

                        connBookmarksList.splice(index, 1)
                        connBookmarksListRepeater.model = [...connBookmarksList]
                    }
                }
                UiBtnUp {
                    visible: connBookmarksList.length > 1
                    onClicked: {
                        moveItemSplice(connBookmarksList, index, index -1)
                        connBookmarksListRepeater.model = [...connBookmarksList]
                    }
                }
            }
        }
    }
}
