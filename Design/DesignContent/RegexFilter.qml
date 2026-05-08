import QtQuick
import Design
import Core
import QtQuick.Layouts
import QtQuick.Controls
import UiComp

ColumnLayout {
    id: regexFilter    
    required property string regexPlaceholderText
    required property var extractTagsAry
    required property string extractTagsField
    signal controlAccepted()

    Flow {
        Layout.fillWidth: true
        Layout.leftMargin:  Constants.font.pixelSize
        Layout.rightMargin:  Constants.font.pixelSize
        spacing: Constants.font.pixelSize
        Repeater {
            model:  extractTags(
                        extractTagsAry,
                        extractTagsField
                        )
            CoreButton {
                text: modelData
                onClicked: {
                    filterByDescription.text = modelData
                }
            }
        }
    }
    CoreTextField {
        Layout.margins:  Constants.font.pixelSize
        id: filterByDescription
        Layout.fillWidth: true
        placeholderText: regexPlaceholderText
        onAccepted: {
            controlAccepted()
        }
    }
    function extractTags(arr, fieldName) {
        var regex = /:\w+/g
        var set = new Set()
        
        for (var i = 0; i < arr.length; i++) {
            var value = arr[i][fieldName]
            if (!value)
                continue
            
            var matches = value.match(regex)
            if (matches) {
                for (var j = 0; j < matches.length; j++) {
                    set.add(matches[j])
                }
            }
        }
        
        // Convert Set → Array of strings
        var result = Array.from(set)
        
        return result
    }
    
    function testFilterByDescription(userInput) {
        const searchRegExp = new RegExp(filterByDescription.text,"i");
        return searchRegExp.test(userInput);
    }
}
