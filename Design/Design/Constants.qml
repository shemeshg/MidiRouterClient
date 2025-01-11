pragma Singleton

import QtQuick
import Bal

//import QtQuick.Studio.Application

QtObject {
    readonly property int width: 800
    readonly property int height: 400

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



    /*
    property StudioApplication application: StudioApplication {
        fontPath: Qt.resolvedUrl("../DesignContent/" + relativeFontDirectory)
    }
    */


    property BalData balData: BalData {}

    enum ServerStatus {
        STOPPED,
        STARTING,
        RUNNING,
        FAILED
    }

    enum FilterType {
        TO_MIDI_DESTINATION,
        TO_CONSOLE,
        TO_NETWORK,
        SCHEDULE_TO,
        FILTER_AND_TRANSFORM
    }

    enum LogTo {
        CLIENT,
        SERVER
    }

}
