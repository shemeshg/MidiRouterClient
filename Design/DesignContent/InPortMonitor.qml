import QtQuick
import Design
import Core
import QtQuick.Layouts


ColumnLayout {
    property string inputName: ""
    property var midiRouteInput: ({})
    Component.onCompleted: {
        inputName = inPortsLoaderId.inPortName
        midiRouteInput = Constants.balData.midiClientConnection.userDataConfig.activePreset.getInputOrCreateByName(inputName)
    }

    CoreButton {
        text: "back"
        onClicked: {
            inPortsId.state = "InPortsList";
            console.log(JSON.stringify(midiRouteInput.monitor.isMonitored))
        }
    }

Layout.fillWidth: true
    CoreLabel {
        text:"Monitoring " + midiRouteInput.midiInputName
    }

    CoreSwitch {
        text: "Monitored"
        checked: midiRouteInput.monitor.isMonitored
        onToggled: {
            midiRouteInput.monitor.isMonitored = checked;
            Constants.balData.applyConfig(() => {
                console.log("client says we have finished applay config");
                //midiRouteInput = Constants.balData.midiClientConnection.userDataConfig.activePreset.getInputOrCreateByName(inputName);
            });
        }
    }
}
