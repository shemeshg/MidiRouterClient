import QtQuick
import Design
import Core
import QtQuick.Layouts
import QtQuick.Controls

Dialog {
    
    id: monitorDialog
    popupType: Popup.Window
    modal: false
    property string inputName: ""
    property bool isClientConnected : {
        return Constants.balData.midiClientConnection.serverStatus
                === Constants.ServerStatus.RUNNING;
    }
    onIsClientConnectedChanged: ()=>{
                                    if (!isClientConnected ){
                                        monitorDialog.close()
                                    }
                                }

    Loader {
        id: ldrId
        property string inputName: ""
        property var midiRouteInput: ({})
        active: midiRouteInput.monitor !== undefined
        sourceComponent:
            Column {
                width: monitorDialog.width - 30
                height: monitorDialog.height
            ScrollView {
                contentHeight: cl.height
                contentWidth: cl.width
                width: parent.width
                height: parent.height
                ColumnLayout {
                    width: parent.width
                    id: scrollerWidthId
                    Layout.fillWidth: true
                }
                ColumnLayout{
                    id: cl
                    RowLayout {
                        CoreLabel {
                            text: inputName
                        }
                        CoreLabel {
                            text: midiRouteInput.monitor.isMonitored ? " (*)" : ""
                            color: CoreSystemPalette.buttonText

                        }
                    }
                    Repeater {
                        id: dialogRepeater
                        Layout.leftMargin:   Constants.font.pixelSize
                        Layout.rightMargin:   Constants.font.pixelSize
                        model: midiRouteInput.monitor.logItems
                        RowLayout {

                            CoreTextArea {
                                Layout.fillWidth: true
                                readOnly: true
                                text: modelData
                            }
                        }
                    }
                }

            }
        }
    }
    
    
    
    onOpened: {
        ldrId.inputName = monitorDialog.inputName
        ldrId.midiRouteInput = Constants.balData.midiClientConnection.userDataConfig.activePreset.getInputOrCreateByName(inputName)
    }
    //focus: true
    contentWidth: parent.width * 0.75
    contentHeight : parent.height * 0.5
    palette.buttonText: CoreSystemPalette.buttonText
    standardButtons: Dialog.Ok
    onClosed: {
        return
    }
    
}
