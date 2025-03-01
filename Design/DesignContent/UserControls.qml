import QtQuick
import Design
import Core
import QtQuick.Layouts
import QtQuick.Controls


ColumnLayout {            
    Layout.fillWidth: true
    id: userControlsId
    function setLoaderToControls(){
        controlLoaderId.sourceComponent = controls
    }

    function setLoaderToDropdowns(){
        controlLoaderId.sourceComponent = dropdowns
    }

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
