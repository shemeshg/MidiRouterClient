import QtQuick
import Design
import Core
import QtQuick.Layouts

ColumnLayout {
    id: inPortsId
    state: "InPortsList"
    Loader {
        id: inPortsLoaderId
        property string inPortName: ""
        Layout.fillWidth: true
        sourceComponent: inPortsListId
    }
    Component {
        id: inPortsListId
        InPortsList {
        }
    }

    Component {
        id: inPorSettingstId
        InPortSettings {
        }
    }

    states: [
        State {
            name: "InPortsList"
            when: inPortsId.state === "InPortsList"
            PropertyChanges {
                target: inPortsLoaderId
                sourceComponent: inPortsListId
            }
        },
        State {
            name: "InPortSettings"
            when: inPortsId.state === "InPortSettings"
            PropertyChanges {
                target: inPortsLoaderId
                sourceComponent: inPorSettingstId
                }
        }
    ]
}
