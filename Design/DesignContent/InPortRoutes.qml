import QtQuick
import Design
import Core
import QtQuick.Layouts
import QtQuick.Controls

ColumnLayout {
    id: inPortRoutesId
    property var midiRouteInput: Constants.balData.midiClientConnection.userDataConfig.activePreset.getInputOrCreateByName(inPortsLoaderId.inPortName)

    state: "InPortsRoutesListFilters"

    Loader {
        id: inPortsRoutesLoaderId
        Layout.fillWidth: true
        sourceComponent: inPortsRoutesListFiltersId
        property var filterObj:({})
    }
    Component {
        id: inPortsRoutesListFiltersId
        InPortsRoutesListFilters {
        }
    }

    Component {
        id: inPortsRoutesFilterToMidi
        InPortsRoutesFilterToMidi {
        }

    }

    states: [
        State {
            name: "InPortsRoutesListFilters"
            when: inPortRoutesId.state === "InPortsRoutesListFilters"
            PropertyChanges {
                target: inPortsRoutesLoaderId
                sourceComponent: inPortsRoutesListFiltersId
            }
        },
        State {
            name: "InPortsRoutesFilterToMidi"
            when: inPortRoutesId.state === "InPortsRoutesFilterToMidi"
            PropertyChanges {
                target: inPortsRoutesLoaderId
                sourceComponent: inPortsRoutesFilterToMidi
            }
        }


    ]

}
