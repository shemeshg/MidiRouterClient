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
        CoreComboBox {
            id: nameId
            Layout.fillWidth: true
            model: ["", ...Constants.balData.midiClientConnection.userDataConfig.connectedOutPorts]

            Component.onCompleted: {
                var index = model.indexOf(inPortsRoutesLoaderId.filterObj.baseMidiRouteInput);
                if (index !== -1) {
                    currentIndex = index;
                }
            }
            onActivated: {
                doSave();
            }
        }

    }
}
