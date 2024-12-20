import QtQuick
import Design
import Core
import QtQuick.Layouts

CoreComboBox {
            id: presetMidiControlOnData1Id
            editable: true
            textRole: "text"
            valueRole: "value"
            model: [
                {
                    value: -1,
                    text: "-"
                },
                ...Array.from({
                    length: 128
                }, (_, i) => ({
                            value: i ,
                            text: (i).toString()
                        }))]
            onAccepted: {
                let idx = model.findIndex(item => item.value === Number(editText)) 
                if (idx === -1){
                    idx = 0;
                }
                currentIndex = idx;
                editText = model[idx].text;
            }            
        }
