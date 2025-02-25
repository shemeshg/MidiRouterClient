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

            property int portNumber: -1
            Component.onCompleted: {
                Constants.balData.getPortNumber(modelData.outputPortnName,(i)=>{
                                                 portNumber = i;
                                                })

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
                    if (i=== modelData.inputVal){return;}
                    modelData.inputVal = i;
                if (portNumber === -1){
                              return;
                          }
                if (modelData.eventType === 0){
                    Constants.balData.sendControlChange(
                       portNumber, modelData.ccId, modelData.inputVal, [modelData.channelId.toString()],()=>{} )
                } else if (modelData.eventType === 1){
                    Constants.balData.sendProgramChange(portNumber, modelData.inputVal, [modelData.channelId.toString()],()=>{})
                } else if (modelData.eventType === 2){
                    Constants.balData.setNonRegisteredParameterInt(
                        portNumber, modelData.nrpnControl, modelData.inputVal, [modelData.channelId.toString()], ()=>{})

                }


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
