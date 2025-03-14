import QtQuick
import Design
import Core
import QtQuick.Layouts
import QtQuick.Controls
import UiComp

ColumnLayout {

    GroupBox {
        Layout.margins:  Constants.font.pixelSize
        Layout.fillWidth: true

        RowLayout {
            Layout.leftMargin: Constants.font.pixelSize
            Layout.rightMargin: Constants.font.pixelSize
            anchors.left: parent.left
            anchors.right: parent.right
            UiTitle {
                title: "Routes"
            }
            Item {
                Layout.fillWidth: true
            }
            UiBtnAdd {
                onClicked: {
                    midiRouteInput.easyConfig.addEasyConfigRoute()
                }

            }
        }
    }


    Repeater {
        model: midiRouteInput.easyConfig.easyConfigRoutes
        GroupBox {
            Layout.leftMargin: Constants.font.pixelSize
            Layout.rightMargin: Constants.font.pixelSize
            Layout.fillWidth: true
            property bool fromKeyOnOff: [1,2,3].indexOf( fromEvent.currentIndex) > -1
            property bool fromEventIsCc: [5,7].indexOf( fromEvent.currentValue) > -1
            property bool toEventIsCc: [5,7].indexOf( toEvent.currentValue) > -1
            property bool toEventIsPc: [8].indexOf( toEvent.currentValue) > -1
            ColumnLayout {
                width: parent.width
                RowLayout {

                    CoreLabel {
                        text: "Destination"
                    }
                    LocalNetMidiOut {
                        toDestinationName: modelData.toDestinationName
                        onUserEdited:()=>{
                                         modelData.toDestinationName =  toDestinationName;
                                     }
                    }
                    UiBtnDel {
                        onClicked: {
                            midiRouteInput.easyConfig.delEasyConfigRoute(index)
                        }
                    }
                }
                RowLayout {

                    ColumnLayout {
                        CoreLabel {
                            text: "From event"
                        }

                        MidiControlEventType {
                            id: fromEvent
                            implicitWidth: Constants.font.pixelSize * 15
                            Component.onCompleted: {
                                currentIndex = model.findIndex(item => item.value === modelData.fromSelectedMidiEventTypeId);
                            }
                            onActivated: {
                                modelData.fromSelectedMidiEventTypeId = currentValue
                                // auto the other
                                modelData.toSelectedMidiEventTypeId = currentValue
                                toEvent.currentIndex = currentIndex
                            }
                        }
                    }
                    ColumnLayout {
                        CoreLabel {
                            text: "From Channel"
                        }
                        MidiControlChannel {
                            Component.onCompleted: {
                                currentIndex = model.findIndex(item => item.value === modelData.fromChannel);
                            }
                            onActivated: {
                                modelData.fromChannel = currentValue
                                // auto the other
                                modelData.toChannel = currentValue
                                toChannel.currentIndex = currentIndex
                            }
                        }
                    }
                    ColumnLayout {
                        visible: fromKeyOnOff
                        CoreLabel {
                            text: "From Zone"
                        }

                        CoreComboBox {
                            textRole: "text"
                            valueRole: "value"
                            model: [
                                {
                                    value: -1,
                                    text: "-"
                                },
                                ...midiRouteInput.easyConfig.zoneNames.map((text, index) => {
                                                                               return { value: index, text: text };
                                                                           })]
                            Component.onCompleted: {
                                currentIndex = model.findIndex(item => item.value === modelData.splitRangeId);
                            }
                            onActivated: {
                                modelData.splitRangeId = currentValue
                            }
                        }
                    }

                    ColumnLayout {
                        visible: fromKeyOnOff
                        CoreLabel {
                            text: "Transpose"
                        }
                        CoreTextField {
                            text: modelData.transpose
                            onTextEdited: ()=>{
                                              modelData.transpose = Number(text)
                                          }
                        }
                    }

                    ColumnLayout {
                        visible: fromEventIsCc
                        CoreLabel {
                            text: fromEvent.currentValue === 5 ? "CC -1==all" : "Nrpn Ctrl (-1 = all)"
                        }
                        CoreTextField {
                            text: modelData.fromData1
                            onTextEdited: ()=>{
                                              modelData.fromData1 = Number(text)
                                          }
                        }

                    }
                    ColumnLayout {
                        visible: fromEventIsCc
                        CoreLabel {
                            text: "From data"
                        }
                        CoreTextField {
                            text: modelData.fromCcOrNrpnStart
                            onTextEdited: ()=>{
                                              modelData.fromCcOrNrpnStart = Number(text)
                                          }
                        }
                    }
                    ColumnLayout {
                        visible: fromEventIsCc
                        CoreLabel {
                            text: "To data"
                        }
                        CoreTextField {
                            text: modelData.fromCcOrNrpnEnd
                            onTextEdited: ()=>{
                                              modelData.fromCcOrNrpnEnd = Number(text)
                                          }
                        }
                    }
                }

                RowLayout {

                    ColumnLayout {
                        CoreLabel {
                            text: "To event"
                        }
                        MidiControlEventType {
                            id: toEvent
                            implicitWidth: Constants.font.pixelSize * 15
                            Component.onCompleted: {
                                currentIndex = model.findIndex(item => item.value === modelData.toSelectedMidiEventTypeId);
                            }
                            onActivated: {
                                modelData.toSelectedMidiEventTypeId = currentValue
                            }
                        }
                    }
                    ColumnLayout {
                        CoreLabel {
                            text: "To Channel"
                        }
                        MidiControlChannel {
                            id: toChannel
                            Component.onCompleted: {
                                currentIndex = model.findIndex(item => item.value === modelData.toChannel);
                            }
                            onActivated: {
                                modelData.toChannel = currentValue
                            }
                        }
                    }
                    ColumnLayout {
                        visible: toEventIsCc
                        CoreLabel {
                            text: toEvent.currentValue === 5 ? "CC -1==all" : "Nrpn Ctrl (-1 = all)"
                        }
                        CoreTextField {
                            text: modelData.toData1
                            onTextEdited: ()=>{
                                              modelData.toData1 = Number(text)
                                          }
                        }
                    }
                    ColumnLayout {
                        visible: toEventIsCc || toEventIsPc
                        CoreLabel {
                            text: "From data"
                        }
                        CoreTextField {
                            text: modelData.toCcOrNrpnStart
                            onTextEdited: ()=>{
                                              modelData.toCcOrNrpnStart = Number(text)
                                          }
                        }
                    }
                    ColumnLayout {
                        visible: toEventIsCc || toEventIsPc
                        CoreLabel {
                            text: "To data"
                        }
                        CoreTextField {
                            text: modelData.toCcOrNrpnEnd
                            onTextEdited: ()=>{
                                              modelData.toCcOrNrpnEnd = Number(text)
                                          }
                        }

                    }

                }
            }
        }
    }
}

