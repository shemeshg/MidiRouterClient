import QtQuick
import Design
import Core
import QtQuick.Layouts
import QtQuick.Controls

Column {
    function setLoaderToControls(){
        controlLoaderId.sourceComponent = controls
    }

    function setLoaderToDropdowns(){
        controlLoaderId.sourceComponent = dropdowns
    }

    ColumnLayout {
        width: parent.width
        id: scrollerWidthId
        Layout.fillWidth: true
    }
    ScrollView {
        contentHeight: userControlsId.height
        contentWidth: userControlsId.width
        width: parent.width
        height: parent.height
        ColumnLayout {
            Layout.fillWidth: true
            width: scrollerWidthId.width - 30
            id: userControlsId

            Loader {
                id: controlLoaderId
                Layout.fillWidth: true
                sourceComponent: editControlsId.checked ? controls : dropdowns
                property var editControlObj: ({})
            }
            Component {
                id: controls
                UserControlsList {
                    activePreset: Constants.balData.midiClientConnection.userDataConfig.activePreset
                    onEditControl: (v)=>{
                                       controlLoaderId.editControlObj = v
                                       controlLoaderId.sourceComponent = userControls;
                                   }
                }
            }
            Component {
                id: dropdowns
                UserControlsDropdowns {
                }
            }

            Component {
                id: userControls
                UserControlsEditControl {
                    onBack: {
                        controlLoaderId.sourceComponent = controls
                    }
                }
            }
        }
    }
}
