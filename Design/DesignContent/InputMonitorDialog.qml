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
    
    Loader {
        id: ldrId
        property string inputName: ""
        property var midiRouteInput: ({})
        active: midiRouteInput.monitor !== undefined
        sourceComponent:
            ColumnLayout{
            CoreLabel {
                text: inputName
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
