import QtQuick
import Design
import Core
import QtQuick.Layouts
import QtQuick.Controls

Column {
    ColumnLayout {
        width: parent.width
        id: scrollerWidthId
        Layout.fillWidth: true
    }
    ScrollView {
        contentHeight: inPortsId.height
        contentWidth: inPortsId.width
        width: parent.width
        height: parent.height
        ColumnLayout {
            id: inPortsId
            width: scrollerWidthId.width - 30
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

            Component {
                id: inPortRoutesId
                InPortRoutes {
                }
            }

            Component {
                id: inPortEasyConfigId
                InPortEasyConfig {
                }
            }

            Component {
                id: inPortMonitorId
                InPortMonitor {
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
                },
                State {
                    name: "InPortRoutes"
                    when: inPortsId.state === "InPortRoutes"
                    PropertyChanges {
                        target: inPortsLoaderId
                        sourceComponent: inPortRoutesId
                    }
                },
                State {
                    name: "InPortEasyConfig"
                    when: inPortsId.state === "InPortEasyConfig"
                    PropertyChanges {
                        target: inPortsLoaderId
                        sourceComponent: inPortEasyConfigId
                    }
                },
                State {
                    name: "InPortMonitor"
                    when: inPortsId.state === "InPortMonitor"
                    PropertyChanges {
                        target: inPortsLoaderId
                        sourceComponent: inPortMonitorId
                    }
                }
            ]
        }
    }
}
