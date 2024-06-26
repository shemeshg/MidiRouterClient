pragma Singleton

import QtQuick 6.2
import QtQuick.Studio.Application
import Bal

QtObject {

    //readonly property int width: 800
    //readonly property int height: 500
    property string relativeFontDirectory: "fonts"

    /* Edit this comment to add your custom font */
    readonly property font font: Qt.font({
                                             "family": Qt.application.font.family,
                                             "pixelSize": Qt.application.font.pixelSize
                                         })
    readonly property font largeFont: Qt.font({
                                                  "family": Qt.application.font.family,
                                                  "pixelSize": Qt.application.font.pixelSize * 1.6
                                              })

    readonly property color backgroundColor: "#EAEAEA"

    property StudioApplication application: StudioApplication {
        fontPath: Qt.resolvedUrl("../../content/" + relativeFontDirectory)
    }

    readonly property SystemPalette systemplate: SystemPalette {
        id: systemPalette
        function isDarkColor(hex) {
            // Convert hex color to RGB values
            let r = parseInt(hex.slice(1, 3), 16)
            let g = parseInt(hex.slice(3, 5), 16)
            let b = parseInt(hex.slice(5, 7), 16)

            // Calculate luminance
            let l = 0.2126 * r + 0.7152 * g + 0.0722 * b

            // Return true if luminance is less than 128, false otherwise
            return l < 128
        }

        colorGroup: SystemPalette.Active

        property bool isDarkTheme: !isDarkColor(systemPalette.text.toString())
    }

    property BalData balData: BalData {}

    enum ServerStatus {
        STOPPED,
        STARTING,
        RUNNING,
        FAILED
    }
}
