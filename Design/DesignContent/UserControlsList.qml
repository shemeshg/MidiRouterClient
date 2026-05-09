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
                enabled: regexFilter.isEmpty()
            }
        }
    }



    RegexFilter {
        id: regexFilter

        regexPlaceholderText: "RegEx filter by description ex. tag1|tag2 (⏎ - send 1st)"
        extractTagsAry: activePreset.userControls
        extractTagsField: "description"
        onControlAccepted: ()=>{
               for (let i = 0; i < controlRepeater.count; i++) {
                   let item = controlRepeater.itemAt(i)
                   if (item && item.visible) {
                       item.cmbSliderId.setVal(item.val, true)
                       break
                   }
               }
        }
    }


    Repeater {
        id: controlRepeater
        model: activePreset.userControls
        ColumnLayout {
            visible: regexFilter.testFilterByDescription(modelData.description)
            property var favBtnsList: []
            property alias cmbSliderId: cmbSliderId

            ComboSilder {
                Layout.leftMargin:  Constants.font.pixelSize
                Layout.rightMargin:  Constants.font.pixelSize


                function getDdAnyData(controlModelData){
                    let ddlists = Constants.balData.
                    midiClientConnection.
                    userDataConfig.dropdownlists;

                    const theEntryFound = ddlists.find(entry => entry.uuid === controlModelData.dropdownListUuid);

                    if (theEntryFound) {
                        const theEntryFoundData = theEntryFound.data.replace(/\n\.\./g, "").trim().split("\n")
                        return theEntryFoundData

                    }
                    return []
                }



                function getCmbModel(controlModelData){

                    let ddlists = Constants.balData.
                    midiClientConnection.
                    userDataConfig.dropdownlists;

                    if (controlModelData.isShowDropdown) {

                        let retList = [];

                        const theEntryFound = ddlists.find(entry => entry.uuid === controlModelData.dropdownListUuid);

                        if (theEntryFound) {                            
                            const theEntryFoundData = theEntryFound.data.replace(/\n\.\./g, "").trim().split("\n")
                            .filter(line => !line.trim().startsWith("PRE-ANY") && !line.trim().startsWith("POST-ANY"))
                            .join("\n");



                            retList = theEntryFoundData.trim().split("\n").map((row, idx) => {
                                                                                   return { text: row.trim().split("|")[0],
                                                                                       fullText: row,
                                                                                       value: idx + controlModelData.minVal };
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

                    cmbSliderId.cmbModel = getCmbModel(modelData);

                    let favBtnsListResult = [];
                    let favBtnsListRegex = /BTN-(\d+)/;
                    for (let i=0;i< cmbSliderId.cmbModel.length; i++){
                        let match = cmbSliderId.cmbModel[i].fullText?.match(favBtnsListRegex);
                        if (match) {
                            favBtnsListResult.push({
                                                 text: cmbSliderId.cmbModel[i].text,
                                                 idx: i,
                                                 value: cmbSliderId.cmbModel[i].value,
                                                 sortOrder: parseInt(match[1])
                                             })

                        }
                    }

                    const sortOrders = favBtnsListResult.map(x => x.sortOrder);
                    const allSame = sortOrders.every(x => x === sortOrders[0]);

                    if (!allSame) {
                        // Only sort when priorities differ
                        favBtnsListResult.sort((a, b) => {
                            if (b.sortOrder !== a.sortOrder) {
                                return a.sortOrder - b.sortOrder;
                            }
                            return a.originalIndex - b.originalIndex; // stable for ties
                        });
                    }
                    favBtnsList = favBtnsListResult;
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

                              let ccOrnrpnControl = -1;
                              if (modelData.eventType === 0){
                                  ccOrnrpnControl = modelData.ccId;
                              } else if (modelData.eventType === 2){
                                  ccOrnrpnControl = modelData.nrpnControl;
                              }

                              Constants.balData.sendUserControl(
                                  modelData.outputPortnName,
                                  [modelData.channelId.toString()],
                                  modelData.isShowDropdown,
                                  getDdAnyData(modelData),
                                  cmbSliderId.val,
                                  modelData.eventType,
                                  ccOrnrpnControl,
                                  ()=>{}
                                  )
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
            Flow {
                Layout.fillWidth: true
                Layout.leftMargin:  Constants.font.pixelSize
                Layout.rightMargin:  Constants.font.pixelSize
                spacing: Constants.font.pixelSize
                Repeater {
                    model: favBtnsList
                    CoreButton {
                        text: modelData.text
                        hooverText: modelData.value
                        onClicked: {
                            cmbSliderId.cmb.currentIndex = modelData.idx
                            cmbSliderId.slider.value = cmbSliderId.cmb.currentValue
                            cmbSliderId.setVal(cmbSliderId.cmb.currentValue, true)                            
                        }
                    }
                }
            }

        }

    }
}
