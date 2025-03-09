import QtQuick
import Design
import Core
import QtQuick.Layouts
import QtQuick.Controls
import UiComp

ColumnLayout {
    property var activePreset: ({})
    signal editControl(var s);

    GroupBox {
        Layout.fillWidth: true
        Layout.margins:  Constants.font.pixelSize
        RowLayout {
            anchors.left: parent.left
            anchors.right: parent.right
            UiTitle {
                title: "User Controls"
            }
            Item {
                Layout.fillWidth: true
            }
            UiBtnAdd {
                onClicked: {
                    activePreset.addUserControl()
                }
            }
        }
    }


    Repeater {        
        model: activePreset.userControls
        ComboSilder {
            Layout.leftMargin:  Constants.font.pixelSize
            Layout.rightMargin:  Constants.font.pixelSize
            function getCmbModel(controlModelData){

                let ddlists = Constants.balData.
                midiClientConnection.
                userDataConfig.dropdownlists;

                if (controlModelData.isShowDropdown) {

                    let retList = [];

                    if (ddlists.length > 0 &&
                            controlModelData.dropdownListId >= 0 && controlModelData.dropdownListId < ddlists.length) {
                        retList = ddlists[controlModelData.dropdownListId].data.trim().split("\n")
                        .map((row,idx)=>{
                                return {text: row, value: idx}
                             });
                    }

                    for (let i = retList.length; retList.length <= controlModelData.maxVal; i++) {
                        retList.push({ text: i.toString(), value: i });
                    }
                    return retList;
                }
                return []
            }

            property int portNumber: -1
            Component.onCompleted: {
                Constants.balData.getPortNumber(modelData.outputPortnName,(i)=>{
                                                 portNumber = i;
                                                })

                cmbSliderId.cmbModel = getCmbModel(modelData)
            }

            id: cmbSliderId
            showEdit: true
            val: modelData.inputVal
            fromVal: modelData.minVal
            toVal: modelData.maxVal
            name: modelData.description
            is64Mode: modelData.is64Mode
            isShowLabel: true
            cmbModel: []
            onSetVal: (i, isForce)=>{
                    if (i=== modelData.inputVal && !isForce){return;}
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
                isSubForm = true;
                editControl(modelData)
            }
        }
    }
}
