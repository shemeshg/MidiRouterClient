import QtQuick
import QtQuick.Controls
import MidiRouterClient

ToolTip {
    id: toolTip
    contentItem: Text {
        color: CoreSystemPalette.text

        text: toolTip.text
        font: Constants.font //Constants.fontSizeNormal()
    }
    background: Rectangle {
        color: CoreSystemPalette.base
    }
}
