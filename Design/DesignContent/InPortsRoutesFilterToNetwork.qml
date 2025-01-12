import QtQuick
import Design
import Core
import QtQuick.Layouts
import QtQuick.Controls

ColumnLayout {
    property var remotePorts: []
    CoreLabel {
        text: "inPortsRoutesFilterToNetwork"
    }
    CoreButton {
        text: "back"
        onClicked: {
            inPortsRoutesLoaderId.filterObj.setFilter( serverName.text,serverPort.text, baseMidiRouteInput.text)
            inPortRoutesId.state = "InPortsRoutesListFilters"
        }
    }
    RowLayout {
        CoreLabel {
            text: "Server name"
        }
        CoreTextField {
            id: serverName
            text: inPortsRoutesLoaderId.filterObj.serverName
            Layout.fillWidth: true
        }
    }
    RowLayout {
        CoreLabel {
            text: "Server port"
        }
        CoreTextField {
            id: serverPort
            text: inPortsRoutesLoaderId.filterObj.serverPort
            Layout.fillWidth: true
        }
    }
    RowLayout {
        CoreLabel {
            text: "Midi port"
        }
        CoreTextField {
            id: baseMidiRouteInput
            text: inPortsRoutesLoaderId.filterObj.baseMidiRouteInput
            Layout.fillWidth: true
        }
    }
    RowLayout {
        CoreButton {
            text: "Query remote midi ports: "
            onClicked: {
                Constants.balData.queryRemoteMidiPorts(serverName.text,serverPort.text, (result)=>{
                              serverStatus.text = result.serverStatus;
                             remotePorts = result.inPorts
                        })
            }
        }
        CoreLabel {
            id: serverStatus
            text: ""
        }
    }
    Repeater {
        model: remotePorts
        RowLayout {
            CoreLabel {
                text: modelData
            }
            CoreButton {
                text: "select"
                onClicked: {
                    baseMidiRouteInput.text = modelData
                }
            }
        }
    }
}
