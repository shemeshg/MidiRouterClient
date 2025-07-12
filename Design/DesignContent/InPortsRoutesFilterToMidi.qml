import QtQuick
import Design
import Core
import QtQuick.Layouts
import QtQuick.Controls
import UiComp

ColumnLayout {
    function doSave(){
        inPortsRoutesLoaderId.filterObj.setFilter( nameId.currentValue)
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
                text: "Edit filter - Route to midi"
            }
        }
    }



    RowLayout {
        Layout.margins:  Constants.font.pixelSize
        CoreLabel {
            text: "Port name"
        }
        ComboBoxOutport {
            id: nameId
            Layout.fillWidth: true
            cmbVal: inPortsRoutesLoaderId.filterObj.baseMidiRouteInput

            onActivated: {
                doSave();
            }
        }

    }
}
