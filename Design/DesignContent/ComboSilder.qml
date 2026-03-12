import QtQuick
import Design
import Core
import QtQuick.Layouts
import QtQuick.Controls
import UiComp

ColumnLayout {
    property int val: 0
    property int fromVal: 0
    property int toVal: 127
    property string name: ""
    property var cmbModel: []
    property bool showEdit: false
    property bool is64Mode: false
    property bool isShowLabel: false
    property bool isShowUpBtn: false
    property bool outputPortnNameMissing: false
    signal del()
    signal edit()
    signal setVal(int i, bool isForce);
    signal setName(string s);
    signal upBtn()


    RowLayout {
        id: row


        CoreLabel {
            visible: outputPortnNameMissing
            text: "❗ "
        }
        CoreTextField {
            text: name
            Layout.fillWidth: true
            onTextEdited: ()=>{
                              setName(text)
                          }
        }
        CoreTextField {
            visible: isShowLabel
            Layout.preferredWidth: Constants.font.pixelSize * (text.length + 1)
            text: is64Mode ? val - Math.floor ((fromVal + toVal + 1 )) / 2 : val
            onTextEdited: ()=>{

                              if (is64Mode){
                                  const offset = Math.floor((fromVal + toVal + 1)) / 2
                                  const rawInt = Number(text) + offset

                                  let index = cmbModel.findIndex(item => item.value.toString() === rawInt.toString());
                                  if (index === -1){return;}
                                  cmb.currentIndex = index

                                  setVal(rawInt, false)
                                  slider.value = rawInt
                              } else {
                                  let index = cmbModel.findIndex(item => item.value.toString() === text);
                                  if (index === -1){return;}
                                  cmb.currentIndex = index

                                  setVal(Number(text), false)
                                  slider.value = Number(text)
                              }


                          }
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
                slider.value = currentValue
                setVal(currentValue, false)
            }

            Component.onCompleted: {
                var index = cmbModel.findIndex(item => item.value.toString() === slider.value.toString());
                currentIndex = index;
            }
        }
        UiBtnEdit {
            visible: showEdit
            onClicked: {
                edit()
            }
        }
        UiBtnDel {
            onClicked: {
                del()
            }
        }

        CoreButton {
            text: "Send"
            onClicked: {
                setVal(slider.value, true)
            }
        }
        UiBtnUp {
            visible: isShowUpBtn
            onClicked: {
                upBtn()
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
            stepSize: 1
            onMoved: {                
                var index = cmbModel.findIndex(item => item.value.toString() === slider.value.toString());
                cmb.currentIndex = index
                setVal(value, false)
            }
        }
    }
}
