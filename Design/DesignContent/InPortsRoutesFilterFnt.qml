import QtQuick
import Design
import Core
import QtQuick.Layouts
import QtQuick.Controls

ColumnLayout {
    CoreLabel {
        text: "InPortsRoutesFilterFnt"
    }
    CoreButton {
        text: "back"
        onClicked: {

            inPortsRoutesLoaderId.filterObj.setFilter(name.text,
                        conditionAction.currentValue,
                        filterChannel.text,
                        filterEvents.text,
                        filterData1.text,
                        filterData2.text
            )

            inPortRoutesId.state = "InPortsRoutesListFilters"
        }
    }
    RowLayout {
        CoreLabel {
            text: "name"
        }
        CoreTextField {
            id: name
            text: inPortsRoutesLoaderId.filterObj.name
        }
    }
    RowLayout {
        CoreLabel {
            text: "Condition Action"
        }
        CoreComboBox {
            id:conditionAction
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
        }
    }
    RowLayout {
        CoreLabel {
            text: "Filter Channel"
        }
        CoreTextField {
            id: filterChannel
            text: inPortsRoutesLoaderId.filterObj.filterChannel
        }
    }
    RowLayout {
        CoreLabel {
            text: "Filter Event"
        }
        CoreTextField {
            id: filterEvents
            text: inPortsRoutesLoaderId.filterObj.filterEvents
        }
    }
    RowLayout {
        CoreLabel {
            text: "Filter Data1"
        }
        CoreTextField {
            id: filterData1
            text: inPortsRoutesLoaderId.filterObj.filterData1
        }
    }
    RowLayout {
        CoreLabel {
            text: "Filter Data2"
        }
        CoreTextField {
            id: filterData2
            text: inPortsRoutesLoaderId.filterObj.filterData2
        }
    }
}
