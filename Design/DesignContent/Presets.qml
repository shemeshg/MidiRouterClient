import QtQuick
import Design
import Core
import QtQuick.Layouts
import QtQuick.Controls

ColumnLayout {
            id: presets
            Layout.fillWidth: true
            CoreLabel {
                text: "Selected preset id:" + Constants.balData.midiClientConnection.userDataConfig.activePresetID
            }
        }
