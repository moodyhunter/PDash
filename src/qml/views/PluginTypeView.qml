import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import pd.mooody.me

Popup {
    id: root
    parent: Overlay.overlay
    width: parent.width
    height: parent.height
    closePolicy: Popup.NoAutoClose
    modal: true
    signal itemSelected(string itemType)

    readonly property int _paddingH: parent.width / 2 - 250
    readonly property int _paddingV: parent.height / 2 - 200
    bottomPadding: _paddingV
    topPadding: _paddingV
    leftPadding: _paddingH
    rightPadding: _paddingH

    background: Rectangle {
        color: "transparent"
    }

    contentItem: PDGlowedRectangle {
        hoverEnabled: false
        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 10
            spacing: 15

            PDLabel {
                font.pixelSize: 20
                Layout.fillWidth: true
                horizontalAlignment: Text.AlignHCenter
                text: qsTr("Please select a component")
            }

            ListView {
                clip: true
                spacing: 10
                Layout.fillWidth: true
                Layout.fillHeight: true
                model: PanelModel.getAllQmlTypes()
                delegate: PDGlowedRectangle {
                    width: parent.width

                    MouseArea {
                        anchors.fill: content
                        onClicked: {
                            console.log("clicked: " + modelData)
                        }
                    }

                    contentItem: RowLayout {
                        readonly property var _data: PanelModel.getQmlInfoFromType(
                                                         modelData)
                        id: content
                        anchors.fill: parent
                        anchors.margins: 5
                        spacing: 10
                        Image {
                            Layout.fillHeight: true
                            source: "file:///home/leroy/Work/Qv2ray/assets/icons/qv2ray.png" // content._data.iconPath
                            sourceSize.width: 96
                            sourceSize.height: 96
                        }

                        ColumnLayout {
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            PDLabel {
                                Layout.fillWidth: true
                                font.pixelSize: 20
                                text: modelData
                            }

                            Item {
                                Layout.fillWidth: true
                            }

                            PDLabel {
                                Layout.fillWidth: true
                                text: qsTr("Description:") + " " + content._data.description
                            }

                            PDLabel {
                                Layout.fillWidth: true
                                text: qsTr("QML Path:") + " " + content._data.qmlPath
                            }
                        }
                    }
                }
            }

            Button {
                Layout.fillWidth: true
                text: qsTr("Cancel")
                onClicked: root.close()
            }
        }
    }
}
