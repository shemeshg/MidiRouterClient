import QtQuick 6.5

QtObject {
    readonly property int x: 100
    readonly property int y: 100
    readonly property int width: 800
    readonly property int height: 500
    function saveWidth(s){}
    function saveHeight(s){}
    function saveX(s){}
    function saveY(s){}

    property int reqServerPortNumber: 12345
    property int serverPort: 12345
    property bool isServerRunning: false
    function stopServer(){
        isServerRunning = false
    }
    function startServer(){
        isServerRunning = true
    }
}
