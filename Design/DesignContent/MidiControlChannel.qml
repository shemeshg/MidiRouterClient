import QtQuick
import Design
import Core
import QtQuick.Layouts

CoreComboBox {
            id: presetMidiControlOnChannelId

            textRole: "text"
            valueRole: "value"
            model: [
                {
                    value: -1,
                    text: "-"
                },
                ...Array.from({
                    length: 16
                }, (_, i) => ({
                            value: i + 1,
                            text: (i + 1).toString()
                        }))]
        }
