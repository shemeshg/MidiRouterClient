import QtQuick
import Design
import Core
import QtQuick.Layouts
import QtQuick.Controls

ColumnLayout {
    CoreLabel {
        text: "inPortsRoutesFilterToConsole"
    }
    CoreButton {
        text: "back"
        onClicked: {
            inPortsRoutesLoaderId.filterObj.setFilter( logTo.currentValue, userdata.text)
            inPortRoutesId.state = "InPortsRoutesListFilters"
        }
    }
    RowLayout {
        CoreLabel {
            text: "Destination"
        }
        CoreComboBox {
            id:logTo
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
        }
    }
    RowLayout {
        CoreLabel {
            text: "User Data"
        }
        CoreTextField {
            id: userdata
            text: inPortsRoutesLoaderId.filterObj.userdata
        }
    }
}
