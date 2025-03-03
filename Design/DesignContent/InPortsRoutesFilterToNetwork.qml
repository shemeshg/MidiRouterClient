import QtQuick
import Design
import Core
import QtQuick.Layouts
import QtQuick.Controls
import UiComp

ColumnLayout {
    property string  serverName: ""
    property int  serverPort: 1234
    property string  midiPort: ""

    signal back();
    signal doSet();


    GroupBox {
        Layout.margins:  Constants.font.pixelSize
        Layout.fillWidth: true


        RowLayout {
            anchors.left: parent.left
            anchors.right: parent.right

            UiBtnBack {
                onClicked: {
                    back()
                }
            }
            Item {
                Layout.fillWidth: true
            }
            CoreLabel {
                text: midiRouteInput.midiInputName
            }
            Item {
                Layout.fillWidth: true
            }
            CoreLabel {
                text: "Edit filter - Network port"
            }
        }
    }

    ColumnLayout {
        Layout.margins:  Constants.font.pixelSize
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
                                  serverPort = Number(text)
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
                color: text === "Failed" ? "darkorange" : CoreSystemPalette.text
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
}
