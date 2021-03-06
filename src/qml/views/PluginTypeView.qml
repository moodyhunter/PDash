import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import pd.mooody.me

Popup {
    id: root
    readonly property int _paddingH: root.width / 2 - 250
    readonly property int _paddingV: root.height / 2 - 200

    bottomPadding: _paddingV
    topPadding: _paddingV
    leftPadding: _paddingH
    rightPadding: _paddingH

    parent: Overlay.overlay
    width: parent.width
    height: parent.height
    closePolicy: Popup.CloseOnEscape
    modal: true

    signal itemSelected(string itemType, size initialSize)

    background: Rectangle {
        color: "transparent"
    }

    contentItem: PDGlowedRectangle {
        hoverEnabled: false
        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 15
            spacing: 24

            PDLabel {
                font.pixelSize: 25
                text: qsTr("Add Component")
            }

            ListView {
                id: list
                clip: true
                spacing: 10
                Layout.fillWidth: true
                Layout.fillHeight: true
                model: PanelModel.getAllQmlTypes()
                delegate: PDGlowedRectangle {
                    hoverEnabled: false
                    width: parent.width

                    MouseArea {
                        anchors.fill: content
                        onClicked: {
                            console.log("clicked: " + modelData)
                            root.itemSelected(modelData,
                                              content._model.initialSize)
                        }
                    }

                    contentItem: RowLayout {
                        readonly property var _model: PanelModel.getQmlInfoFromType(
                                                          modelData)
                        id: content
                        anchors.fill: parent
                        anchors.margins: 5
                        spacing: 10
                        Image {
                            Layout.preferredHeight: 96
                            Layout.preferredWidth: 96
                            Layout.fillHeight: true
                            source: content._model.iconPath
                            sourceSize.width: 80
                            sourceSize.height: 80
                        }

                        ColumnLayout {
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            PDLabel {
                                Layout.fillWidth: true
                                font.pixelSize: 20
                                text: modelData
                            }

                            PDLabel {
                                Layout.fillWidth: true
                                text: content._model.description + " ("
                                      + content._model.initialSize.height + "x"
                                      + content._model.initialSize.width + ")"
                            }
                        }
                    }
                }
            }
        }
    }
}
