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
