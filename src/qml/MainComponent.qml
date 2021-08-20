import QtQuick
import QtQuick.Layouts
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Shapes

import pd.mooody.me

import "components"

Item {
    id: rootComponent
    anchors.fill: parent
    property bool editing: true

    MainWindowModel {
        id: mwModel
    }

    property var activityStreamModel: [{
            "type": "GitHub Notifications",
            "title": "Daguerreo/NodeEditor #14",
            "text": "Daguerreo/NodeEditor #14\nCMake: respect specified Qt version from QT_VERSION_MAJOR",
            "id": "5611652a-9463-48e7-8372-4a248a5f0ed0",
            "date": "Just Now"
        }, {
            "type": "Mail - myemail@mydomain.com",
            "title": "Watch a demo of Windows 365 - Microsoft Tech News",
            "text": "Watch an overview of Windows 365 to see how it delivers your PC in the cloud.",
            "id": "a169bd1d-4672-4e4d-a4b6-9f37a5f19b4f",
            "date": "6 Hours Ago"
        }, {
            "type": "Jira Ticket",
            "title": "New Change in QTBUG-87471",
            "text": "Daguerreo/NodeEditor #14\nCMake: respect specified Qt version from QT_VERSION_MAJOR",
            "id": "b9907466-cfc5-416c-8c34-53bde71a5a98",
            "date": "Yesterday"
        }, {
            "type": "Due Date",
            "title": "Coursework Due Passed",
            "text": "CS999 Coursework Due",
            "id": "9f8c4cc4-cead-4869-981c-c8737b94ebeb",
            "date": "Yesterday"
        }]

    //Drawer {
    //    width: 0.23 * rootWindow.width
    //    height: rootWindow.height
    //    Label {
    //        text: "Content goes here!"
    //        anchors.centerIn: parent
    //    }
    //}
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
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
            }
        }

        ColumnLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true

            RowLayout {
                Label {
                    text: "Dashboard"
                    Layout.leftMargin: 10
                    Layout.topMargin: 5
                    Layout.bottomMargin: 5
                    Layout.fillWidth: true
                    font.pointSize: 30
                    color: Qt.darker(AppTheme.text, 1.5)
                }
                Button {
                    text: "Print Sizes"
                    onClicked: console.log(grid.getPositions())
                }
            }

            Rectangle {
                Layout.fillWidth: true
                height: 2
                color: AppTheme.handlerHoverColor
            }

            SplitView {
                Layout.fillWidth: true
                Layout.fillHeight: true
                id: splitview
                spacing: 40

                handle: Rectangle {
                    color: SplitHandle.pressed ? Qt.darker(
                                                     AppTheme.dark,
                                                     1.5) : (SplitHandle.hovered ? AppTheme.handlerHoverColor : AppTheme.border)
                    implicitWidth: 5
                    radius: 5
                }

                PanelGrid {
                    SplitView.fillWidth: true
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    id: grid
                    model: mwModel.panels
                    CircularButton {
                        z: 99
                        backgroundcolor: grid.editMode ? AppTheme.highlight : AppTheme.background
                        textcolor: grid.editMode ? AppTheme.background : AppTheme.highlight
                        anchors.margins: 10
                        anchors.right: parent.right
                        anchors.bottom: parent.bottom
                        text: "Edit"
                        onClicked: grid.editMode = !grid.editMode
                    }
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
                        model: rootComponent.activityStreamModel
                        control: ColumnLayout {
                            Label {
                                color: AppTheme.text
                                Layout.fillWidth: true
                                text: modelData.type
                                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                            }
                            Label {
                                color: AppTheme.text
                                Layout.fillWidth: true
                                text: modelData.title
                                wrapMode: Text.WrapAnywhere
                            }
                            Label {
                                color: AppTheme.text
                                Layout.fillWidth: true
                                text: modelData.id
                                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                            }
                            Label {
                                color: AppTheme.text
                                Layout.fillWidth: true
                                text: modelData.text
                                wrapMode: Text.WrapAnywhere
                            }
                            Label {
                                color: AppTheme.text
                                Layout.fillWidth: true
                                text: modelData.date
                                wrapMode: Text.WrapAnywhere
                            }
                        }
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
}
