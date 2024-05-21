import QtQuick
import MidiRouterClient
import QtQuick.Layouts
import Core
import QtQuick.Controls

ColumnLayout {
    id: fromGroupBox
    property string title: ""
    required property Component body

    CoreLabel {
        text: title
        leftPadding: Constants.font.pixelSize
        topPadding: Constants.font.pixelSize
        visible: Boolean(title)
    }

    CoreGroupBox {
        Layout.fillWidth: true
        id: cgb
        Loader {
            width: cgb.width
            sourceComponent: body
        }
    }
}
