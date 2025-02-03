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
            function getCmbModel(){

                let ddlists = Constants.balData.
                midiClientConnection.
                userDataConfig.dropdownlists;

                if (modelData.isShowDropdown &&
                        modelData.dropdownListId >= 0 ) {

                    return  ddlists[modelData.dropdownListId].data.trim().split("\n")
                    .map((row,idx)=>{
                            return {text: row, value: idx}
                         });





                }
                return []
            }


            id: cmbSliderId
            showEdit: true
            val: modelData.inputVal
            fromVal: modelData.minVal
            toVal: modelData.maxVal
            name: modelData.description
            is64Mode: modelData.is64Mode
            isShowLabel: true
            cmbModel: getCmbModel()
            onSetVal: (i)=>{
                modelData.inputVal = i
                console.log("Missing implement send midi")
                      }
            onSetName: (s)=>{
                modelData.description = s;
                       }
            onDel: {
                activePreset.delUserControl(index)
            }
            onEdit: {
                editControl(modelData)
            }
        }
    }
}
