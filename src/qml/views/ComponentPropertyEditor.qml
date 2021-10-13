import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import pd.mooody.me

Popup {
    id: root

    signal editFinished(var props)

    property string componentType

    function setComponentProperties(props) {
        propModel.setCurrentPropertyValues(props)
    }

    readonly property int _paddingH: root.width / 2 - 200
    readonly property int _paddingV: root.height / 2 - 225

    bottomPadding: _paddingV
    topPadding: _paddingV
    leftPadding: _paddingH
    rightPadding: _paddingH

    parent: Overlay.overlay
    width: parent.width
    height: parent.height
    closePolicy: Popup.CloseOnEscape
    modal: true
    onClosed: editFinished({})

    background: Rectangle {
        color: "transparent"
    }

    ComponentPropertyModel {
        id: propModel
        componentType: root.componentType
    }

    contentItem: PDGlowedRectangle {
        hoverEnabled: false
        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 15

            PDLabel {
                font.pixelSize: 25
                text: qsTr("Property Editor")
            }

            PDLabel {
                text: qsTr("Component ID: ") + root.componentType
                font.italic: true
            }

            Rectangle {
                color: "#999999"
                Layout.preferredHeight: 1
                Layout.fillWidth: true
            }

            ListView {
                id: propertyList
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.topMargin: 10
                spacing: 24
                clip: true
                model: propModel
                ScrollBar.vertical: ScrollBar {
                    policy: ScrollBar.AlwaysOn
                }
                delegate: RowLayout {
                    width: propertyList.width - 20

                    PDLabel {
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        font.pixelSize: 15
                        text: description
                    }

                    Loader {
                        Layout.fillHeight: true
                        Layout.minimumWidth: 50
                        Component {
                            id: cieditor
                            SpinBox {
                                id: sb
                                value: model.value
                                from: -99999
                                to: 99999
                                onValueChanged: {
                                    model.value = sb.value
                                }
                            }
                        }

                        Component {
                            id: cbeditor
                            RowLayout {
                                CheckBox {
                                    id: cb
                                    checked: model.value
                                    onCheckedChanged: {
                                        model.value = checked
                                    }
                                }
                                PDLabel {
                                    text: cb.checked ? qsTr("True") : qsTr(
                                                           "False")
                                }
                            }
                        }

                        Component {
                            id: cseditor
                            TextInput {
                                text: model.value
                                color: AppTheme.text
                                selectByMouse: true
                                font: fixedFont
                                onTextChanged: {
                                    model.value = text
                                }
                            }
                        }

                        // 1        => Boolean
                        // 10       => String
                        // Others   => Integer
                        sourceComponent: type === 1 ? cbeditor : (type === 10 ? cseditor : cieditor)
                    }
                }
            }

            RowLayout {
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignRight
                Button {
                    text: qsTr("Save")
                    onClicked: {
                        root.editFinished(propModel.getCurrentPropertyValues())
                    }
                }
                Button {
                    text: qsTr("Discard")
                    onClicked: {
                        root.editFinished({})
                    }
                }
            }
        }
    }
}
