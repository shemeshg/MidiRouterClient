import QtQuick
import Design
import Core
import QtQuick.Layouts
import QtQuick.Controls

ColumnLayout {
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
        }
    }
    RowLayout {
        CoreLabel {
            text: "Server port"
        }
        CoreTextField {
            id: serverPort
            text: inPortsRoutesLoaderId.filterObj.serverPort
        }
    }
    RowLayout {
        CoreLabel {
            text: "Midi port"
        }
        CoreTextField {
            id: baseMidiRouteInput
            text: inPortsRoutesLoaderId.filterObj.baseMidiRouteInput
        }
    }
    CoreButton {
        text: "Query remote midi ports"
        onClicked: {

        }
    }
}
