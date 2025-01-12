import QtQuick
import Design
import Core
import QtQuick.Layouts
import QtQuick.Controls

ColumnLayout {
    CoreLabel {
        text: "InPortsRoutesFilterSchedule"
    }
    CoreButton {
        text: "back"
        onClicked: {
            inPortsRoutesLoaderId.filterObj.setFilter( defferedType.currentValue, defferedTo.text)
            inPortRoutesId.state = "InPortsRoutesListFilters"
        }
    }

    RowLayout {
        CoreLabel {
            text: "Deffered Type"
        }
        CoreComboBox {
            id:defferedType
            Layout.fillWidth: true
            textRole: "text"
            valueRole: "value"
            model: [
                { value: Constants.DefferedType.IN_SPP, text: "In Spp" },
                { value: Constants.DefferedType.IN_BAR,text: "In Bar" },
                { value: Constants.DefferedType.AT_SPP,text: "At Spp" },
                { value: Constants.DefferedType.AT_BAR,text: "At Bar" },
                { value: Constants.DefferedType.QUANTIZE_SPP,text: "Quantize Spp" },
                { value: Constants.DefferedType.QUANTIZE_BAR,text: "Quantize Bar" }
            ]
            Component.onCompleted: {
                    currentIndex = inPortsRoutesLoaderId.filterObj.defferedType;
            }
        }
    }
    RowLayout {
        CoreLabel {
            text: "Deffered To"
        }
        CoreTextField {
            id: defferedTo
            text: inPortsRoutesLoaderId.filterObj.defferedTo
        }
    }

}
