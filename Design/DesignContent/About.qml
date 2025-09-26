import Design
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Core
import QtQuick.Dialogs
import UiComp

Column {
    ColumnLayout {
        width: parent.width
        id: scrollerWidthId
        Layout.fillWidth: true
    }

    ScrollView {
        contentHeight: aboutId.height
        contentWidth: aboutId.width
        width: parent.width
        height: parent.height

        ColumnLayout {
            Layout.fillWidth: true
            width: scrollerWidthId.width - 30
            id: aboutId

            property string homebrewVersion: ""
            Layout.margins:  Constants.font.pixelSize


            GroupBox {
                Layout.margins:  Constants.font.pixelSize
                Layout.fillWidth: true


                RowLayout {
                    anchors.left: parent.left
                    anchors.right: parent.right

                    UiBtnBack {
                        visible: !Constants.balData.midiClientConnection.userDataConfig.criticalErrorMsg
                        onClicked: {
                            headerBarId.state = aboutPreviousStr
                            isSubForm = false
                        }
                    }
                    Item {
                        Layout.fillWidth: true
                    }
                    CoreLabel {
                        text: "Settings & About"
                    }
                    Item {
                        Layout.fillWidth: true
                    }
                    CoreLabel {
                        text: ""
                    }
                }
            }





            FileDialog {
                id: fileDialogDownload
                title: "Please choose a .json file to download"
                fileMode: FileDialog.SaveFile
                onAccepted: {
                    Constants.balData.midiClientConnection.
                    userDataConfig.downloadJson(currentFile);
                }
                nameFilters: ["json (*.json)"]

            }
            FileDialog {
                id: fileDialogUpload
                title: "Please choose a .json file to upload"
                fileMode: FileDialog.OpenFile
                onAccepted: {
                    Constants.balData.uploadJson(currentFile,()=>{});
                }
                nameFilters: ["json (*.json)"]

            }

            ColumnLayout {
                Layout.leftMargin:   Constants.font.pixelSize
                Layout.rightMargin:   Constants.font.pixelSize
                RowLayout {

                    CoreLabel {
                        text: "Font size (Empty for default, requires reopen) "
                        color: CoreSystemPalette.text
                    }
                    CoreTextField {
                        id: defaultFontSize
                        text: Constants.balData.defaultFontSize
                        Layout.fillWidth: true
                    }
                    CoreButton {
                        text: "set"
                        onClicked: {
                            Constants.balData.saveDefaultFontSize(defaultFontSize.text)
                        }
                    }
                }
                RowLayout {
                    CoreButton {
                        text: "Download client settings"
                        onClicked: {
                            fileDialogDownload.open()
                        }
                        icon.source: Qt.resolvedUrl(
                                         "icons/download_2_24dp_E3E3E3_FILL0_wght400_GRAD0_opsz24.svg")

                        icon.color: CoreSystemPalette.buttonText
                        palette.buttonText: CoreSystemPalette.buttonText
                    }
                }
                RowLayout {
                    CoreButton {
                        text: "Upload client settings"
                        onClicked: {
                            fileDialogUpload.open();
                        }
                        icon.source: Qt.resolvedUrl(
                                         "icons/upload_2_24dp_E3E3E3_FILL0_wght400_GRAD0_opsz24.svg")

                        icon.color: CoreSystemPalette.buttonText
                        palette.buttonText: CoreSystemPalette.buttonText
                    }
                }
                RowLayout {
                    CoreLink{
                        text: "Link to booted server config " +
                              ( Constants.balData.midiClientConnection.userDataConfig.criticalErrorMsg ?
                                  "Deleting this file will reset the server configuration to default." : "")

                        onClicked: () => {
                                       Constants.balData.openCashFolder()
                                   }

                    }
                }

                CoreLabel {
                    text: `
                    <h2>About</h2>
                    `
                    wrapMode: Text.WordWrap
                    Layout.fillWidth: true
                }



                CoreLink{
                    id: hyperlinkBtn

                    text: "Midi Router Client " + Qt.application.version

                    onClicked: () => {
                                   Qt.openUrlExternally("https://sourceforge.net/projects/midi-router-client/");
                               }

                }



                CoreLabel {
                    text: Constants.balData.qtVer()
                }

                CoreLink{

                    text: "<h2>ⓘ</h2>"

                    onClicked: () => {
                                   Qt.openUrlExternally("https://shemeshg.github.io/MidiRouterClient-mdbook/");
                               }

                }

                CoreLabel {
                text: `
                <h2>License</h2>
                <p>Copyright 2020 shemeshg</p>
                <p>Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:</p>
                <p>The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.</p>
                <p>THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.</p>
                `
                wrapMode: Text.WordWrap
                Layout.fillWidth: true
            }
            }
            Item {
                Layout.fillHeight: true
            }
        }

    }
}
