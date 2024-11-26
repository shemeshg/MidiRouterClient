import QtQuick
import Design
import QtQuick.Layouts
import Core


ColumnLayout {
    id: fromGroupBox
    property string title: ""
    required property Component body

    CoreLabel {
        text: fromGroupBox.title
        leftPadding: Constants.font.pixelSize
        topPadding: Constants.font.pixelSize
        visible: Boolean(fromGroupBox.title)
    }

    CoreGroupBox {
        Layout.fillWidth: true
        id: cgb
        Loader {
            width: cgb.width
            sourceComponent: fromGroupBox.body
        }
    }
}
