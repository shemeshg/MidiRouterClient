import QtQuick
import Design
import Core
import QtQuick.Layouts
import QtQuick.Controls

ColumnLayout {
    property int val: 0
    property int fromVal: 0
    property int toVal: 127
    property string name: ""
    property var cmbModel: []
    property bool showEdit: false
    property bool is64Mode: false
    signal del()
    signal edit()
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
        CoreLabel {
            visible: cmbModel.length === 0
            text: is64Mode ? val - Math.floor ((toVal + 1 )) / 2 : val
        }

        CoreComboBox {
            visible: cmbModel.length !== 0
            function cmbLen(){
                let a = cmbModel.reduce((max, item) => {
                                            return item.text.length > max ? item.text.length : max;
                                          }, 0);
                a = a < 5 ? 5: a;
                return Constants.font.pixelSize * a;

            }
            id: cmb
            implicitWidth: cmbLen();

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
        CoreButton {
            text: "del"
            onClicked: {
                del()
            }
        }
        CoreButton {
            visible: showEdit
            text: "edit"
            onClicked: {
                edit()
            }
        }

    }

    RowLayout{
        CoreSlider {
            Layout.fillWidth: true
            id: slider
            from: fromVal
            value: val
            to: toVal
            onMoved: {
                cmb.currentIndex = value
                setVal(value)
            }
        }
    }
}
