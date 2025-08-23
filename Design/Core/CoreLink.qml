import QtQuick

CoreLabel{
    id: coreLabel
    signal clicked()
    color: CoreSystemPalette.isDarkTheme ? "Light blue" : "Dark blue"
    MouseArea {
        anchors.fill: parent
        cursorShape: Qt.PointingHandCursor
        onClicked: () => {
                       coreLabel.clicked()
                   }
    }
}
