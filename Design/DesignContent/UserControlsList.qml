import QtQuick
import Design
import Core
import QtQuick.Layouts
import QtQuick.Controls
import UiComp

ColumnLayout {
    property var activePreset: ({})
    signal editControl(var s);


    function parseMidiTokens(description, portNumber, aryChannelId) {
        // One combined regex that captures ANY token in order
        const tokenRegex = /\b(CC-(\d+)-(\d+)|PC-(\d+)|NRPN-(\d+)-(\d+))\b/g;

        let tokenFound = false;
        let match;

        while ((match = tokenRegex.exec(description)) !== null) {

            // CC
            if (match[2] !== undefined && match[3] !== undefined) {
                const cc1 = Number(match[2]);
                const cc2 = Number(match[3]);
                doCC(cc1, cc2);
                Constants.balData.sendControlChange(
                            portNumber, cc1, cc2, aryChannelId,()=>{} )

                tokenFound = true;
                continue;
            }

            // PC
            if (match[4] !== undefined) {
                const pc = Number(match[4]);
                Constants.balData.sendProgramChange(portNumber, pc, aryChannelId,()=>{})
                tokenFound = true;
                continue;
            }

            // NRPN
            if (match[5] !== undefined && match[6] !== undefined) {
                const n1 = Number(match[5]);
                const n2 = Number(match[6]);
                Constants.balData.setNonRegisteredParameterInt(
                            portNumber, n1, n2, aryChannelId, ()=>{})
                tokenFound = true;
                continue;
            }
        }
        return tokenFound;
    }



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

                    const theEntryFound = ddlists.find(entry => entry.uuid === controlModelData.dropdownListUuid);
                    if (theEntryFound) {
                        retList = theEntryFound.data.trim().split("\n").map((row, idx) => {
                                                                                return { text: row, value: idx + controlModelData.minVal };
                                                                            });
                    }


                    for (let i = retList.length + controlModelData.minVal;
                         i <= controlModelData.maxVal; i++) {
                        retList.push({ text: (modelData.is64Mode ?
                                                  (i - Math.floor ((modelData.minVal + modelData.maxVal + 1 )) / 2).toString() + " - " + i:
                                                  i.toString()
                                              ), value: i });
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
            outputPortnNameMissing: (Constants.balData.midiClientConnection.userDataConfig.connectedOutPorts.indexOf(modelData.outputPortnName) === -1)
            cmbModel: []
            onSetVal: (i, isForce)=>{
                          //isForece, means send cmd although control already set to that value
                          if (i=== modelData.inputVal && !isForce){return;}
                          modelData.inputVal = i;
                          if (portNumber === -1){
                              return;
                          }


                          if (parseMidiTokens(cmbSliderId.cmbModel[cmbSliderId.val].text , portNumber,  [modelData.channelId.toString()])){return;}

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
            isShowUpBtn: activePreset.userControls.length > 1
            onUpBtn: {
                activePreset.moveUserControl(index, index - 1);
            }

        }
    }
}
