import QtQuick
import Design
import Core
import QtQuick.Layouts
import QtQuick.Controls

ColumnLayout {
            CoreLabel {
                text: "inPortsRoutesFilterToMidi"
            }
            CoreButton {
                text: "back"
                onClicked: {
                    inPortsRoutesLoaderId.filterObj.setFilter( nameId.currentValue)
                    inPortRoutesId.state = "InPortsRoutesListFilters"
                }
            }


            RowLayout {
                CoreLabel {
                    text: "portName"
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
                }
            }
        }
