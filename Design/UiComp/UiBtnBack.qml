import Core
import QtQuick

CoreButton {
    id: codeBtn
    hooverText: "<b>⎋</b> back"
    icon.name: "back"
    icon.source: Qt.resolvedUrl(
                     "icons/arrow_back_ios_24dp_E3E3E3_FILL0_wght400_GRAD0_opsz24.svg")

    icon.color: CoreSystemPalette.buttonText
    palette.buttonText: CoreSystemPalette.buttonText

    Shortcut {
        enabled: codeBtn.visible && codeBtn.enabled
        sequences: [StandardKey.Cancel]
        onActivated: codeBtn.click()
    }

}
