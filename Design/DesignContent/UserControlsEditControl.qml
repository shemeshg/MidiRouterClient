import QtQuick
import Design
import Core
import QtQuick.Layouts
import QtQuick.Controls


ColumnLayout {
    property var control: ({})
    signal back();
    CoreButton {
        text: "back"
        onClicked: {
            back();
        }


    }

    CoreLabel {
        text: "editControl" + JSON.stringify(control)
    }
}
