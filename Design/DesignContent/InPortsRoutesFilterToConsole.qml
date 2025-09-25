import QtQuick
import Design
import Core
import QtQuick.Layouts
import QtQuick.Controls
import UiComp

ColumnLayout {
    function doSave(){
        inPortsRoutesLoaderId.filterObj.setFilter( logTo.currentValue, userdata.text)
    }

    GroupBox {
        Layout.margins:  Constants.font.pixelSize
        Layout.fillWidth: true


        RowLayout {
            anchors.left: parent.left
            anchors.right: parent.right

            UiBtnBack {
                onClicked: {
                    inPortRoutesId.state = "InPortsRoutesListFilters"
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
                text: "Edit filter - Log to"
            }
        }
    }

    RowLayout {
        Layout.leftMargin:   Constants.font.pixelSize
        Layout.rightMargin:   Constants.font.pixelSize
        CoreLabel {
            text: "Destination"
        }
        CoreComboBox {
            id:logTo
            enabled: inPortsRoutesLoaderId.isEnabled
            Layout.fillWidth: true
            textRole: "text"
            valueRole: "value"
            model: [
                { value: Constants.LogTo.CLIENT, text: "Client" },
                { value: Constants.LogTo.SERVER,text: "Server" },
            ]
            Component.onCompleted: {
                    currentIndex = inPortsRoutesLoaderId.filterObj.logTo;
            }
            onActivated: {
                doSave()
            }
        }
    }
    RowLayout {
        Layout.margins:  Constants.font.pixelSize
        CoreLabel {
            text: "User Data"
        }
        CoreTextArea {
            id: userdata
            enabled: inPortsRoutesLoaderId.isEnabled
            Layout.fillWidth: true
            text: inPortsRoutesLoaderId.filterObj.userdata
            property bool processing: true
            onTextChanged: {
                if (!processing) {
                    processing = true
                    doSave()
                }
            }
            Keys.onPressed: {
                processing = false
            }
        }
    }
}
