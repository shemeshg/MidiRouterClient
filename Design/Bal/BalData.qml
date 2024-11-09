import QtQuick 6.5

QtObject {
    readonly property int x: 100
    readonly property int y: 100
    readonly property int width: 800
    readonly property int height: 500
    function saveWidth(s) {}
    function saveHeight(s) {}
    function saveX(s) {}
    function saveY(s) {}

    property int reqServerPortNumber: 12345
    property int serverPort: 12345
    property bool isServerRunning: false
    property string clientServerName: "localhost"
    property bool isClientConnectLocal: false
    property bool isAutoStartServer: false
    property bool isAutoConnectClient: false
    property int clientPortNumber: 12345

    function onApplicationStarted(){}
    function saveIsClientConnectLocal(){}
    function saveIsAutoConnectClient(){}
    function saveIsAutoStartServer(){}


    function stopServer() {
        isServerRunning = false
    }
    function startServer() {
        isServerRunning = true
    }

    property QtObject midiClientConnection: QtObject {
        property string serverStatusText: "Not Running"
        property int serverStatus: 0
        property QtObject userDataConfig: QtObject {
            property var virtualInPorts: ["virtual port1", "virtual port2"]
            property int activePresetID: 1
            property var dropdownlists: [{"name": "popo","data": "aaa\nbbb"},{"name": "t2","data": "po\nlo"}]
            property var midiRoutePresets: [
                {
                    "easyConfig": {
                        "inputZonesAndRoutes": {}
                    },
                    "isEnabled": true,
                    "isSendAllUserControls": false,
                    "jsRouter": {
                        "jsToServers": []
                    },
                    "midiControlOff": {
                        "channel": -1,
                        "data1": -1,
                        "data2": -1,
                        "eventTypeId": 0,
                        "portName": "",
                        "presetMidiType": 0,
                        "presetUuid": "0f8ac474-40b9-4097-b992-0b68bad0e084"
                    },
                    "midiControlOn": {
                        "channel": -1,
                        "data1": -1,
                        "data2": -1,
                        "eventTypeId": 0,
                        "portName": "",
                        "presetMidiType": 1,
                        "presetUuid": "0f8ac474-40b9-4097-b992-0b68bad0e084"
                    },
                    "midiRouteInputs": {},
                    "name": "Default preset",
                    "userControls": [],
                    "uuid": "0f8ac474-40b9-4097-b992-0b68bad0e084"
                },
                {
                    "easyConfig": {
                        "inputZonesAndRoutes": {}
                    },
                    "isEnabled": true,
                    "isSendAllUserControls": false,
                    "jsRouter": {
                        "jsToServers": []
                    },
                    "midiControlOff": {
                        "channel": -1,
                        "data1": -1,
                        "data2": -1,
                        "eventTypeId": 0,
                        "portName": "",
                        "presetMidiType": 0,
                        "presetUuid": "0f8ac474-40b9-4097-b992-0b68bad0e084"
                    },
                    "midiControlOn": {
                        "channel": -1,
                        "data1": -1,
                        "data2": -1,
                        "eventTypeId": 0,
                        "portName": "",
                        "presetMidiType": 1,
                        "presetUuid": "0f8ac474-40b9-4097-b992-0b68bad0e084"
                    },
                    "midiRouteInputs": {},
                    "name": "another preset",
                    "userControls": [],
                    "uuid": "0f8ac474-40b9-4097-b992-0b68bad0e084"
                }
                ]
        }

    }

    function saveClientPortNumber(i){
        //dummy
    }

    function setAsyncServerStatusAndText(i, cb) {
        midiClientConnection.serverStatus = i
        midiClientConnection.serverStatusText = "StatusId: " + midiClientConnection.serverStatus
        cb()
    }

    function startClient() {
        midiClientConnection.serverStatus = 2
        midiClientConnection.serverStatusText = "Server running"
    }

    function stopClient() {
        midiClientConnection.serverStatus = 0
        midiClientConnection.serverStatusText = "Stopped"
    }


}
