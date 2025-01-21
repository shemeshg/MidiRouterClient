import QtQuick
import Design
import Core
import QtQuick.Layouts
import QtQuick.Controls

ColumnLayout {
    property int val: 0
    property var cmbModel: []
    CoreComboBox {
        id: cmb
        Layout.fillWidth: true
        textRole: "text"
        valueRole: "value"
        model: cmbModel
        onActivated: {
            slider.value = currentIndex
        }

        Component.onCompleted: {
            currentIndex = val;
        }
    }

    CoreSlider {
        id: slider
        from: 0
        value: val
        to: 127
        Layout.fillWidth: true
        onMoved: {
            cmb.currentIndex = value
        }
    }
}
