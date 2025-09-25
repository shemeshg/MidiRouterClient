import QtQuick
import Design
import Core
import QtQuick.Layouts
import QtQuick.Controls
import UiComp

ColumnLayout {
    function doSave(){
        inPortsRoutesLoaderId.filterObj.setFilter(name.text,
                                                  conditionAction.currentValue,
                                                  filterChannel.text,
                                                  filterEvents.text,
                                                  filterData1.text,
                                                  filterData2.text
                                                  )
    }

    GroupBox {
        Layout.margins:  Constants.font.pixelSize
        Layout.fillWidth: true


        RowLayout {
            anchors.left: parent.left
            anchors.right: parent.right

            UiBtnBack {
                onClicked: {


                    inPortRoutesId.state = "InPortsRoutesListFilters"
                }
            }
            Item {
                Layout.fillWidth: true
            }
            CoreLabel {
                text: midiRouteInput.midiInputName + " - " + inPortsRoutesLoaderId.filterObj.name
            }
            Item {
                Layout.fillWidth: true
            }
            CoreLabel {
                text: "Edit filter - Filter Transform"
            }
        }
    }


    ColumnLayout {
        Layout.leftMargin:   Constants.font.pixelSize
        Layout.rightMargin:   Constants.font.pixelSize


        RowLayout {
            CoreLabel {
                text: "name"
            }
            CoreTextField {
                id: name
                enabled: inPortsRoutesLoaderId.isEnabled
                Layout.fillWidth: true
                text: inPortsRoutesLoaderId.filterObj.name
                onTextEdited: {
                    doSave()
                }
            }
        }
        RowLayout {
            CoreLabel {
                text: "Condition Action"
            }
            CoreComboBox {
                id:conditionAction
                enabled: inPortsRoutesLoaderId.isEnabled
                Layout.fillWidth: true
                textRole: "text"
                valueRole: "value"
                model: [
                    { value: Constants.ConditionAction.DO_NOT_DELETE, text: "Do not delete" },
                    { value: Constants.ConditionAction.DELETE_IF_NOT_MET_CONDITION, text: "Delete if not met condition" },
                    { value: Constants.ConditionAction.DELETE_IF_MET_CONDITION,text: "Delete if met condition" },
                ]
                Component.onCompleted: {
                    currentIndex = inPortsRoutesLoaderId.filterObj.conditionAction;
                }
                onActivated: {
                    doSave()
                }
            }
        }
        RowLayout {
            CoreLabel {
                text: "Filter Channel"
            }
            CoreTextField {
                id: filterChannel
                enabled: inPortsRoutesLoaderId.isEnabled
                Layout.fillWidth: true
                text: inPortsRoutesLoaderId.filterObj.filterChannel
                onTextEdited: {
                    doSave()
                }
            }
        }
        RowLayout {
            CoreLabel {
                text: "Filter Event"
            }
            CoreTextField {
                enabled: inPortsRoutesLoaderId.isEnabled
                id: filterEvents
                Layout.fillWidth: true
                text: inPortsRoutesLoaderId.filterObj.filterEvents
                onTextEdited: {
                    doSave()
                }
            }
        }
        RowLayout {
            CoreLabel {
                text: "Filter Data1"
            }
            CoreTextField {
                enabled: inPortsRoutesLoaderId.isEnabled
                id: filterData1
                Layout.fillWidth: true
                text: inPortsRoutesLoaderId.filterObj.filterData1
                onTextEdited: {
                    doSave()
                }
            }
        }
        RowLayout {
            CoreLabel {
                text: "Filter Data2"
            }
            CoreTextField {
                enabled: inPortsRoutesLoaderId.isEnabled
                id: filterData2
                Layout.fillWidth: true
                text: inPortsRoutesLoaderId.filterObj.filterData2
                onTextEdited: {
                    doSave()
                }
            }
        }
    }
}
