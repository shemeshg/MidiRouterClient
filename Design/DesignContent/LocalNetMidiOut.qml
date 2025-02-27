import QtQuick
import Design
import Core
import QtQuick.Layouts
import QtQuick.Controls

RowLayout{
    id: localNetMidiOut
    property string toDestinationName: ""
    property bool isNetMode: toDestinationName.includes(":")
    signal userEdited()

    function parseMidiPortName(completeMidiPortName) {
        let regex = /^([a-zA-Z0-9._-]+):(\d+)(\/([\ a-zA-Z0-9._-]+)?)?$/;
        let match = completeMidiPortName.match(regex);

        if (match) {
            let serverName = match[1];
            let serverPort = match[2];
            let midiPort = match[4] || "";

            return {
                serverName: serverName,
                serverPort: serverPort,
                midiPort: midiPort
            };
        } else {
            return null;
        }
    }

    function setNetModeFields(){
        if (!isNetMode){
            return;
        }
        let netParams = parseMidiPortName(toDestinationName);
        if (!netParams){return}
        serverName.text = netParams.serverName
        serverPort.text = netParams.serverPort

        remotePorts.model = [...new Set(["",netParams.midiPort])]
        var index = remotePorts.model.indexOf(netParams.midiPort);
        if (index !== -1) {
            remotePorts.currentIndex = index;
        }
    }

    Component.onCompleted: {
        setNetModeFields()

    }

    CoreComboBox {
        visible: !isNetMode
        id: nameId
        Layout.fillWidth: true
        model:
            [...new Set(
                ["",toDestinationName, ...Constants.balData.midiClientConnection.userDataConfig.connectedOutPorts]
                )]

        onActivated: {
            toDestinationName = currentText
            userEdited()
            var index = model.indexOf(toDestinationName);
            if (index !== -1) {
                currentIndex = index;
            }
        }

        Component.onCompleted: {

            var index = model.indexOf(modelData.toDestinationName);
            if (index !== -1) {
                currentIndex = index;
            }

        }
    }
    RowLayout{
        visible: isNetMode
        CoreTextField {
            id: serverName
            text: "localhost"
        }
        CoreLabel {
            text:":"
        }
        CoreTextField {
            id: serverPort
            text: "12345"
        }
        CoreButton {
            text: "query"
            onClicked: {
                Constants.balData.queryRemoteMidiPorts(serverName.text,serverPort.text, (result)=>{
                                                           serverStatus.text = result.serverStatus;
                                                           remotePorts.model = ["",...result.inPorts]
                                                       })
            }
        }
        CoreLabel {
            visible: text === "Failed"
            id: serverStatus
            text:""
        }
        CoreComboBox {
            id: remotePorts
            Layout.fillWidth: true
            onActivated: {
                toDestinationName = `${serverName.text}:${serverPort.text}/${remotePorts.currentText}`
                userEdited()
                nameId.model = [...new Set(
                                    ["",toDestinationName, ...Constants.balData.midiClientConnection.userDataConfig.connectedOutPorts]
                                    )]
                var index = nameId.model.indexOf(toDestinationName);
                if (index !== -1) {
                    nameId.currentIndex = index;
                }
            }
        }
    }
    CoreButton {
        text: isNetMode ? "local port" : "net port"
        onClicked: {
            isNetMode = !isNetMode
            setNetModeFields()
        }
    }
}
