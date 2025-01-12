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

    Component {
        id: inPortsRoutesFilterToConsole
        InPortsRoutesFilterToConsole {
        }
    }

    Component {
        id: inPortsRoutesFilterToNetwork
        InPortsRoutesFilterToNetwork {
        }
    }

    Component {
        id: inPortsRoutesFilterSchedule
        InPortsRoutesFilterSchedule
        {
        }
    }

    Component {
        id: inPortsRoutesFilterFnt
        InPortsRoutesFilterFnt {
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
        },
        State {
            name: "InPortsRoutesFilterToConsole"
            when: inPortRoutesId.state === "InPortsRoutesFilterToConsole"
            PropertyChanges {
                target: inPortsRoutesLoaderId
                sourceComponent: inPortsRoutesFilterToConsole
            }
        },
        State {
            name: "InPortsRoutesFilterToNetwork"
            when: inPortRoutesId.state === "InPortsRoutesFilterToNetwork"
            PropertyChanges {
                target: inPortsRoutesLoaderId
                sourceComponent: inPortsRoutesFilterToNetwork
            }
        },
        State {
            name: "InPortsRoutesFilterSchedule"
            when: inPortRoutesId.state === "InPortsRoutesFilterSchedule"
            PropertyChanges {
                target: inPortsRoutesLoaderId
                sourceComponent: inPortsRoutesFilterSchedule
            }
        },
        State {
            name: "InPortsRoutesFilterFnt"
            when: inPortRoutesId.state === "InPortsRoutesFilterFnt"
            PropertyChanges {
                target: inPortsRoutesLoaderId
                sourceComponent: inPortsRoutesFilterFnt
            }
        }



    ]

}
