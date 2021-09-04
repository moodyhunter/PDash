import QtQuick
import QtQuick.Layouts
import QtQuick.Window
import QtQuick.Controls

import pd.mooody.me

import "components"

Item {
    id: rootComponent
    anchors.fill: parent
    property bool editing: true

    RowLayout {
        anchors.fill: parent
        spacing: 0

        Rectangle {
            width: 90
            color: AppTheme.background
            opacity: AppTheme.backgroundOpacity
            Layout.fillHeight: true

            Rectangle {
                width: 2
                color: Qt.darker(parent.color, 2)
                Layout.fillHeight: true
            }
        }

        ColumnLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true

            RowLayout {
                Label {
                    text: qsTr("Dashboard")
                    Layout.leftMargin: 10
                    Layout.topMargin: 5
                    Layout.bottomMargin: 5
                    Layout.fillWidth: true
                    font.pointSize: 30
                    color: Qt.darker(AppTheme.text, 1.5)
                }
            }

            Rectangle {
                Layout.fillWidth: true
                height: 2
                color: AppTheme.handlerHover
            }

            SplitView {
                Layout.fillWidth: true
                Layout.fillHeight: true
                id: splitview
                spacing: 40

                handle: Rectangle {
                    color: SplitHandle.pressed ? Qt.darker(
                                                     AppTheme.dark,
                                                     1.5) : (SplitHandle.hovered ? AppTheme.handlerHover : AppTheme.border)
                    implicitWidth: 5
                    radius: 5
                }

                PanelGrid {
                    SplitView.fillWidth: true
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    id: grid
                }

                ColumnLayout {
                    SplitView.maximumWidth: 500
                    SplitView.minimumWidth: 150
                    SplitView.preferredWidth: 350
                    id: column

                    Text {
                        color: Qt.darker(AppTheme.text, 1.5)
                        text: qsTr("All activity")
                        font.pointSize: 22
                        Layout.fillWidth: true
                        Layout.leftMargin: 10
                    }

                    ActivityListView {
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        Layout.leftMargin: 10
                    }

                    Item {
                        Layout.fillWidth: true
                        height: 60
                        Rectangle {
                            color: AppTheme.background
                            anchors.fill: parent
                        }
                        Label {
                            anchors.fill: parent
                            text: "Bottom Footer"
                        }
                    }
                }
            }
        }
    }

    LoginPage {
        id: login
        parent: rootWindow.contentItem
        width: rootComponent.width
        height: rootComponent.height
    }
    Component.onCompleted: {
        login.open()
        login.makeFocus()
        rootWindow.color = hasBackgroundEffect ? Qt.transparent : AppTheme.dark
    }
}
