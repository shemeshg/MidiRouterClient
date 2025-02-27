import QtQuick
import Design
import Core
import QtQuick.Layouts
import QtQuick.Controls

ColumnLayout {
    property string  serverName: ""
    property int  serverPort: 1234
    property string  midiPort: ""

    signal back();
    signal doSet();

    CoreLabel {
        text: "Remote port"
    }
    CoreButton {
        text: "back"
        onClicked: {
            back()

        }
    }
    RowLayout {
        CoreLabel {
            text: "Server name"
        }
        CoreTextField {

            text: serverName
            onTextEdited: ()=>{
                          serverName = text
                        doSet();
                          }
            Layout.fillWidth: true
        }
    }
    RowLayout {
        CoreLabel {
            text: "Server port"
        }
        CoreTextField {
            text: serverPort
            onTextEdited: ()=>{
                          serverPort = text
                            doSet();
                          }
            Layout.fillWidth: true
        }
    }
    RowLayout {
        CoreLabel {
            text: "Midi port"
        }
        CoreTextField {
            id: baseMidiRouteInput
            text: midiPort
            onTextEdited: ()=>{
                          midiPort = text;
                              doSet();
                          }
            Layout.fillWidth: true
        }
    }
    RowLayout {
        CoreButton {
            text: "Query remote midi ports: "
            onClicked: {
                Constants.balData.queryRemoteMidiPorts(serverName,serverPort, (result)=>{
                              serverStatus.text = result.serverStatus;
                             remotePorts.model = result.inPorts
                        })
            }
        }
        CoreLabel {
            id: serverStatus
            text: ""
        }
    }
    Repeater {
        id: remotePorts
        RowLayout {
            CoreLabel {
                text: modelData
            }
            CoreButton {
                text: "select"
                onClicked: {
                    baseMidiRouteInput.text = modelData
                    midiPort = modelData
                    doSet();
                }
            }
        }
    }
}
