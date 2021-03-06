import QtQuick
import QtQuick.Layouts
import QtQuick.Window
import QtQuick.Controls

import pd.mooody.me

Window {
    id: rootWindow
    width: 1300
    height: 700
    title: qsTr("PDash - The Personal Dashboard")
    visible: true
    color: AppTheme.dark

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

                ListView {
                    anchors.fill: parent
                    spacing: 5
                    boundsBehavior: Flickable.StopAtBounds
                    model: ["Dashboard", "PDClock", "PDClock2", "Settings", "About"]
                    delegate: Rectangle {
                        border.color: AppTheme.border
                        width: parent.width
                        height: width
                        color: AppTheme.background
                        PDLabel {
                            anchors.fill: parent
                            text: modelData
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }
                    }
                }
            }

            Rectangle {
                width: 2
                color: Qt.darker(AppTheme.background, 1.5)
                Layout.fillHeight: true
            }

            ColumnLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true

                RowLayout {
                    PDLabel {
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

                    GridPanelsView {
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

                        Rectangle {
                            Layout.fillWidth: true
                            height: 60
                            color: AppTheme.background
                            PDLabel {
                                anchors.fill: parent
                                text: "Bottom Footer"
                            }
                        }
                    }
                }
            }
        }

        LoginView {
            id: login
            parent: rootWindow.contentItem
            width: rootComponent.width
            height: rootComponent.height
        }

        Component.onCompleted: {
            login.open()
            login.makeFocus()
        }
    }
}
