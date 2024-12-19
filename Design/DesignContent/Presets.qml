import QtQuick
import Design
import Core
import QtQuick.Layouts

ColumnLayout {
    id: presets
    state: "ListPresets"
    Layout.fillWidth: true

    Loader {
        id: presetsLoaderId
        property int presetIndex: -1
        Layout.fillWidth: true
    }

    Component {
        id: editPresetId
        
        EditPreset {
        }
    }

    Component {
        id: listPresetsId
        ListPresets {
        }
    }
    states: [
        State {
            name: "ListPresets"
            when: presets.state === "ListPresets"
            PropertyChanges {
                target: presetsLoaderId
                sourceComponent: listPresetsId
            }
        },
        State {
            name: "EditPreset"
            when: presets.state === "EditPreset"
            PropertyChanges {
                target: presetsLoaderId
                sourceComponent: editPresetId
            }
        }
    ]
}
