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


    CoreTextField {
        Layout.margins:  Constants.font.pixelSize
        id: filterByDescription
        Layout.fillWidth: true
        placeholderText: "RegEx filter by description ex. tag1|tag2 (⏎ - send 1st)"
        onAccepted: {
            for (let i = 0; i < controlRepeater.count; i++) {
                let item = controlRepeater.itemAt(i)
                if (item && item.visible) {
                    item.setVal(item.val, true)
                    break
                }
            }
        }
    }

    function testFilterByDescription(userInput) {
        const searchRegExp = new RegExp(filterByDescription.text,"i");
        return searchRegExp.test(userInput);
    }

    Repeater {
        id: controlRepeater
        model: activePreset.userControls
        ComboSilder {
            Layout.leftMargin:  Constants.font.pixelSize
            Layout.rightMargin:  Constants.font.pixelSize
            visible: testFilterByDescription(modelData.description)

            function getDdAnyData(controlModelData){
                let ddlists = Constants.balData.
                midiClientConnection.
                userDataConfig.dropdownlists;

                const theEntryFound = ddlists.find(entry => entry.uuid === controlModelData.dropdownListUuid);

                if (theEntryFound) {
                    const theEntryFoundData = theEntryFound.data.trim().split("\n")
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
                        const theEntryFoundData = theEntryFound.data.trim().split("\n")
                        .filter(line => !line.startsWith("PRE-ANY") && !line.startsWith("POST-ANY"))
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
    }
}
