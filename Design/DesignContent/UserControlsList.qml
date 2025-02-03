import QtQuick
import Design
import Core
import QtQuick.Layouts
import QtQuick.Controls


ColumnLayout {
    property var activePreset: ({})
    signal editControl(var s);
    CoreLabel {
        text:  "User Controls: "
    }
    RowLayout {
        CoreButton {
            text: "Send all"
            onClicked: {
                activePreset.sendAllUserControls()
            }
        }

        CoreButton {
            text: "Add"
            onClicked: {
                activePreset.addUserControl()
            }
        }
    }
    Repeater {
        model: activePreset.userControls
        ComboSilder {
            id: cmbSliderId
            showEdit: true
            val: modelData.inputVal
            fromVal: modelData.minVal
            toVal: modelData.maxVal
            name: modelData.description
            is64Mode: modelData.is64Mode
            isShowLabel: cmbSliderId.cmbModel.length === 0
            cmbModel: [
                /*
                  { text: "whatever", value: 2 },
                  { text: "something", value: 3 },
                  { text: "more text", value: 1 },
                  */
            ]
            onSetVal: (i)=>{
                modelData.inputVal = i
                console.log("Missing implement send midi")
                      }
            onSetName: (s)=>{
                modelData.description = s;
                       }
            onDel: {
                console.log("deleting")
            }
            onEdit: {
                editControl(modelData)
            }
        }
    }
}
