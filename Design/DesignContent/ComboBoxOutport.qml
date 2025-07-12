import QtQuick
import Design
import Core
import QtQuick.Layouts
import QtQuick.Controls
import UiComp

CoreComboBox {
    id: cmb
    textRole: "text"
    valueRole: "value"
    required property string cmbVal
    
    Component.onCompleted: {
        let list = [{value: "", text: ""},
                    ...Constants.balData.midiClientConnection.userDataConfig.connectedOutPorts.map(item => ({ value: item, text: item }))
            ]
        if (Constants.balData.midiClientConnection.userDataConfig.connectedOutPorts.indexOf(cmbVal) === -1){
            list.push({ value: cmbVal, text: "❌ " + cmbVal })
        }
        
        
        var index = list.findIndex(item => item.value === cmbVal);
        cmb.model = list
        if (index !== -1) {
            currentIndex = index;
        }
    }

}
