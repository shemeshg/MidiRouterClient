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

    ComboBoxOutport {
        visible: !isNetMode
        id: nameId
        Layout.fillWidth: true
        cmbVal: toDestinationName


        onActivated: {
            toDestinationName = currentValue
            userEdited()
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
                nameId.cmbVal = toDestinationName
                nameId.setOnCompleted();
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
