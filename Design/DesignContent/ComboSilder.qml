import QtQuick
import Design
import Core
import QtQuick.Layouts
import QtQuick.Controls

ColumnLayout {
    property int val: 0
    property string name: ""
    property var cmbModel: []
    signal del()
    signal setVal(int i);
    signal setName(string s);



    RowLayout {
        id: row
        CoreTextField {
            text: name
            Layout.fillWidth: true
            onTextEdited: ()=>{
                              setName(text)
                          }
        }
        CoreComboBox {
            id: cmb
            implicitWidth: Constants.font.pixelSize * 10

            textRole: "text"
            valueRole: "value"
            model: cmbModel
            onActivated: {
                slider.value = currentIndex
                setVal(currentIndex)
            }

            Component.onCompleted: {
                currentIndex = val;
            }
        }
    }

    RowLayout{
        CoreSlider {
            Layout.fillWidth: true
            id: slider
            from: 0
            value: val
            to: 127
            onMoved: {
                cmb.currentIndex = value
                setVal(value)
            }
        }
        CoreButton {
            text: "del"
            onClicked: {
                del()
            }
        }
    }
}
