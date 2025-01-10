import QtQuick
import Design
import Core
import QtQuick.Layouts
import QtQuick.Controls

ColumnLayout {
            CoreLabel {
                text: "inPortsRoutesFilterToMidi"
            }
            CoreButton {
                text: "back"
                onClicked: {
                    inPortRoutesId.state = "InPortsRoutesListFilters"
                }
            }
        }
