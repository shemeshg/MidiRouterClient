import QtQuick
import QtQuick.Controls
import Design
import Core
import QtQuick.Layouts
import UiComp

ColumnLayout {

    GroupBox {
        Layout.margins:  Constants.font.pixelSize
        Layout.fillWidth: true
        RowLayout {

            anchors.left: parent.left
            anchors.right: parent.right
            UiTitle {
                title: "Connected in ports"
            }
        }
    }


    Repeater {
        model: Constants.balData.midiClientConnection.userDataConfig.connectedInPorts
        RowLayout {
            Layout.leftMargin:  Constants.font.pixelSize
            Layout.rightMargin:  Constants.font.pixelSize
            CoreButton {
                text: "Settings"
                onClicked: {
                    inPortsLoaderId.inPortName = modelData;
                    isSubForm = true
                    inPortsId.state = "InPortSettings";
                }
            }
            CoreButton {
                implicitWidth: Constants.font.pixelSize * 10
                text: "Routes " + ( getRoutesCount(modelData) > 0 ? "(" + getRoutesCount(modelData) +")" : "")
                onClicked: {
                    inPortsLoaderId.inPortName = modelData;
                    isSubForm = true
                    inPortsId.state = "InPortRoutes";
                }
            }
            CoreButton {
                implicitWidth: Constants.font.pixelSize * 12
                text: "EasyConfig " + ( getEasyConfigCount(modelData) > 0 ? "(" + getEasyConfigCount(modelData) +")" : "")
                onClicked: {
                    isSubForm = true
                    inPortsLoaderId.inPortName = modelData;
                    isEasyConfigForm = true
                    inPortsId.state = "InPortEasyConfig";
                }
            }

            CoreButton {
                text: "Del"
                onClicked: {
                    Constants.balData.midiClientConnection.userDataConfig.activePreset.delInputByName(modelData)
                }
            }
            CoreButton {
                text: "Monitor"
                onClicked: {
                    inPortsLoaderId.inPortName = modelData;
                    isSubForm = true
                    inPortsId.state = "InPortMonitor";
                }
            }
            CoreLabel {
                text: (hasRoutesWithMissingOutput(modelData) ? "❗ " : "") + modelData
            }
        }
    }

    function getEasyConfigCount(inputName){
        let currentEasyConfigRoutesLen = Constants.balData.midiClientConnection.userDataConfig.activePreset.midiRouteInputs.
        filter(row=>{return row?.midiInputName === inputName})?.[0]?.easyConfig.easyConfigRoutes.length
        if (currentEasyConfigRoutesLen){
            return currentEasyConfigRoutesLen;
        } else {
            return 0;
        }
    }

    function getRoutesCount(inputName){
        let currentRoutesLen = Constants.balData.midiClientConnection.userDataConfig.activePreset.midiRouteInputs.
        filter(row=>{return row?.midiInputName === inputName})?.[0]?.midiRouterChains.
        filter(row=>{return !row.isEasyConfig && !row.isRunForPresetOnAndOff}).length
        if (currentRoutesLen){
            return currentRoutesLen;
        } else {
            return 0;
        }
    }

    function hasRoutesWithMissingOutput(inputName) {
        const config = Constants.balData.midiClientConnection.userDataConfig;
        const routeInput = config.activePreset.midiRouteInputs
            .find(r => r?.midiInputName === inputName);

        const chains = routeInput?.midiRouterChains;
        if (!chains) return false;

        for (const chain of chains) {
            const outputPorts = chain.midiRoutersFilters
                .filter(f => f.filterType === 0)
                .map(f => f.baseMidiRouteInput);

            for (const port of outputPorts) {
                if (config.connectedOutPorts.indexOf(port) === -1) {
                    return true; // missing output found
                }
            }
        }

        return false;
    }


    function getDisconnectedPorts(){
        let currentPresetInputs = Constants.balData.midiClientConnection.userDataConfig.activePreset.midiRouteInputs.map(row=>{return row.midiInputName})

        return currentPresetInputs.filter(item=>{return !Constants.balData.midiClientConnection.userDataConfig.connectedInPorts.includes(item)});
    }

    CoreLabel {
        Layout.topMargin: Constants.font.pixelSize
        Layout.leftMargin: Constants.font.pixelSize
        text: "<h3>Not connected</h3>"
        visible: getDisconnectedPorts().length > 0
    }
    Repeater {
        model: getDisconnectedPorts()
        RowLayout {
            Layout.leftMargin:  Constants.font.pixelSize
            Layout.rightMargin:  Constants.font.pixelSize
            CoreButton {
                text: "Settings"
                onClicked: {
                    inPortsLoaderId.inPortName = modelData;
                    isSubForm = true
                    inPortsId.state = "InPortSettings";
                }
            }
            CoreButton {
                implicitWidth: Constants.font.pixelSize * 10
                text: "Routes " + ( getRoutesCount(modelData) > 0 ? "(" + getRoutesCount(modelData) +")" : "")
                onClicked: {
                    inPortsLoaderId.inPortName = modelData;
                    isSubForm = true
                    inPortsId.state = "InPortRoutes";
                }
            }
            CoreButton {
                implicitWidth: Constants.font.pixelSize * 12
                text: "EasyConfig " + ( getEasyConfigCount(modelData) > 0 ? "(" + getEasyConfigCount(modelData) +")" : "")
                onClicked: {
                    isSubForm = true
                    inPortsLoaderId.inPortName = modelData;
                    isEasyConfigForm = true
                    inPortsId.state = "InPortEasyConfig";
                }
            }
            CoreButton {
                text: "Del"
                onClicked: {
                    Constants.balData.midiClientConnection.userDataConfig.activePreset.delInputByName(modelData)
                }
            }
            CoreLabel {
                text: modelData
            }
        }
    }

}
