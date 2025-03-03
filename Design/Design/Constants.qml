pragma Singleton

import QtQuick
import Bal

//import QtQuick.Studio.Application

QtObject {
    readonly property int width: 800
    readonly property int height: 400

    property string relativeFontDirectory: "fonts"


    function defaultFontSize(){
        let f= Number(Constants.balData.defaultFontSize)
        if (f){
            return f;
        } else {
            return Qt.application.font.pixelSize;
        }
    }

    /* Edit this comment to add your custom font */
    readonly property font font: Qt.font({
                                             "family": Qt.application.font.family,
                                             "pixelSize": defaultFontSize()
                                         })
    readonly property font largeFont: Qt.font({
                                                  "family": Qt.application.font.family,
                                                  "pixelSize": defaultFontSize() * 1.6
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

    enum DefferedType {
        IN_SPP,
        IN_BAR,
        AT_SPP,
        AT_BAR,
        QUANTIZE_SPP,
        QUANTIZE_BAR
    }

    enum  ConditionAction {
            DO_NOT_DELETE,
            DELETE_IF_NOT_MET_CONDITION,
            DELETE_IF_MET_CONDITION
        }

}
