import QtQuick
import Design
import Core
import QtQuick.Layouts

CoreComboBox {
    model: [
        {
            value: 0,
            text: "[] - -"
        },
        {
            value: 1,
            text: "[8, 9] - Note on/off"
        },
        {
            value: 2,
            text: "[9] - Note off"
        },
        {
            value: 3,
            text: "[8] - Note on"
        },
        {
            value: 4,
            text: "[10] - keyaftertouch"
        },
        {
            value: 5,
            text: "[11] - controlchange"
        },
        {
            value: 7,
            text: "[100] - nrpn"
        },
        {
            value: 8,
            text: "[12] - programchange"
        },
        {
            value: 9,
            text: "[13] - channelaftertouch"
        },
        {
            value: 10,
            text: "[14] - pitchbend"
        },
    ]
    textRole: "text"
    valueRole: "value"
}
