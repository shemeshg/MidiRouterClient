import QtQuick
import Design
import Core
import QtQuick.Layouts
import UiComp

ColumnLayout {
    id: inPortsSettings14BitId
    signal selectedItemsModified()
    property var selectedItems: []
        RowLayout {
            CoreLabel {
                text: "<h2>14Bit CC</h2>"
            }
        }
        RowLayout {
            CoreLabel {
                text: "Channel"
            }
            CoreTextField {
               id: cc14bitChannel
               text: "1"
            }
            CoreLabel {
                text: "CC"
            }
            CoreTextField {
                id: cc14bitCc
                text: "0"
            }
            UiBtnAdd{
                onClicked: {
                    cc14bitErr.text = ""
                    if (
                            Number(cc14bitChannel.text) < 1 ||
                            Number(cc14bitChannel.text) > 16 ||
                            Number(cc14bitCc.text) < 0 ||
                            Number(cc14bitCc.text) > 17
                          ) {
                            cc14bitErr.text = "14bit requires Channel 1..16 cc 0..16"
                            return;
                          }

                          if (
                            selectedItems.filter((row) => {
                              return (
                                row.channel === Number(cc14bitChannel.text)  &&
                                row.cc === Number(cc14bitCc.text)
                              );
                            }).length > 0
                          ) {
                            cc14bitErr.text = "Item already in list"
                            return;
                          }
                          selectedItems = [...selectedItems,{channel:
                                        Number(cc14bitChannel.text),
                                        cc: Number(cc14bitCc.text)}];
                          selectedItemsModified();


                }
            }
            CoreLabel {
                visible: text !==""
                id: cc14bitErr
                text: ""
                color: "darkorange"
            }
        }

        function filterSelectedItems(cc, channel){
            let a = selectedItems.map(row=>{

                                          return {cc:row.cc,  channel: row.channel}
                                      })
            selectedItems = a.filter(item => {return !(item.cc === cc
                                                     && item.channel === channel)} );
            selectedItemsModified();
        }


        Repeater {
            id: chanelCcRepeaterId

            model: selectedItems
            RowLayout {
                signal testSignal();
                CoreLabel {
                    text: `channel ${modelData.channel} cc ${modelData.cc}`
                }
                UiBtnDel {
                    onClicked: {
                        filterSelectedItems(modelData.cc, modelData.channel)

                    }
                }                
            }
        }
    }
