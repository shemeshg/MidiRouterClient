import QtQuick
import Design
import Core
import QtQuick.Layouts
import QtQuick.Controls
import UiComp

ColumnLayout {
    function doSave(){
        inPortsRoutesLoaderId.filterObj.setFilter( defferedType.currentValue, defferedTo.text)
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
                text: midiRouteInput.midiInputName
            }
            Item {
                Layout.fillWidth: true
            }
            CoreLabel {
                text: "Edit filter - Schedule"
            }
        }
    }


    RowLayout {
        Layout.leftMargin:   Constants.font.pixelSize
        Layout.rightMargin:   Constants.font.pixelSize
        CoreLabel {
            text: "Deffered Type"
        }
        CoreComboBox {
            id:defferedType
            enabled: inPortsRoutesLoaderId.isEnabled
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
            onActivated: {
                doSave()
            }
        }
    }
    RowLayout {
        Layout.leftMargin:   Constants.font.pixelSize
        Layout.rightMargin:   Constants.font.pixelSize
        CoreLabel {
            text: "Deffered To"
        }
        CoreTextField {
            enabled: inPortsRoutesLoaderId.isEnabled
            id: defferedTo
            text: inPortsRoutesLoaderId.filterObj.defferedTo
            onTextEdited: {
                doSave()
            }
        }

    }

}
