import QtQuick
import Design
import Core
import QtQuick.Layouts
import QtQuick.Controls


ColumnLayout {
    property var activePreset: ({})
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
                console.log(
                            JSON.stringify(activePreset.userControls)
                            )
            }
        }
    }
    Repeater {
        model: activePreset.userControls
        ComboSilder {
            showEdit: true
            val: modelData.inputVal
            fromVal: modelData.minVal
            toVal: modelData.maxVal
            name: modelData.description
            cmbModel: [

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
                console.log("editing")
            }
        }
    }
}
