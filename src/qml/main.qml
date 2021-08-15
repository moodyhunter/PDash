import QtQuick
import QtQuick.Layouts
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Shapes

import "components"

Window {
    width: 1300
    height: 700
    visible: true
    title: qsTr("PD - The Personal Dashboard")
    id: rootWindow
    color: activeTheme.dark

    property bool editing: true

    Themes {
        id: activeTheme
        state: "DarkState"
    }

    property var panelModel: [{
            "row": 1,
            "column": 1,
            "rowSpan": 5,
            "columnSpan": 6
        }, {
            "row": 6,
            "column": 13,
            "rowSpan": 10,
            "columnSpan": 6
        }, {
            "row": 6,
            "column": 1,
            "rowSpan": 10,
            "columnSpan": 12
        }, {
            "row": 1,
            "column": 13,
            "rowSpan": 5,
            "columnSpan": 6
        }, {
            "row": 1,
            "column": 7,
            "rowSpan": 5,
            "columnSpan": 6
        }]

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
        Rectangle {
            width: 90
            color: activeTheme.background
            Layout.fillHeight: true
        }

        ColumnLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true

            RowLayout {
                Label {
                    text: "Dashboard"
                    Layout.fillWidth: true
                    font.pointSize: 30
                    color: Qt.darker(activeTheme.text, 1.5)
                }
                Button {
                    text: "Print Sizes"
                    onClicked: console.log(grid.getPositions())
                }
            }

            Rectangle {
                Layout.fillWidth: true
                height: 2
                color: activeTheme.handlerHoverColor
            }
            SplitView {
                Layout.fillWidth: true
                Layout.fillHeight: true
                id: splitview
                spacing: 40

                handle: Rectangle {
                    color: SplitHandle.pressed ? Qt.darker(
                                                     activeTheme.dark,
                                                     1.5) : (SplitHandle.hovered ? activeTheme.handlerHoverColor : activeTheme.border)
                    implicitWidth: 5
                    radius: 5
                }

                //            CircularButton {
                //                text: "Push"
                //                size: 60
                //                backgroundcolor: "green"
                //                bordercolor: "red"
                //                onClicked: console.log("OK?")
                //            }
                PanelGrid {
                    SplitView.fillWidth: true
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    id: grid
                    columns: 20
                    rows: 20
                    columnSpacing: 15
                    rowSpacing: 15
                    model: panelModel
                    CircularButton {
                        z: 99
                        backgroundcolor: grid.editMode ? activeTheme.highlight : activeTheme.background
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

                    ActivityListView {
                        model: activityStreamModel
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        Layout.margins: 10
                        control: ColumnLayout {
                            Label {
                                color: activeTheme.text
                                Layout.fillWidth: true
                                text: modelData.type
                                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                            }
                            Label {
                                color: activeTheme.text
                                Layout.fillWidth: true
                                text: modelData.title
                                wrapMode: Text.WrapAnywhere
                            }
                            Label {
                                color: activeTheme.text
                                Layout.fillWidth: true
                                text: modelData.id
                                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                            }
                            Label {
                                color: activeTheme.text
                                Layout.fillWidth: true
                                text: modelData.text
                                wrapMode: Text.WrapAnywhere
                            }
                            Label {
                                color: activeTheme.text
                                Layout.fillWidth: true
                                text: modelData.date
                                wrapMode: Text.WrapAnywhere
                            }
                        }
                    }
                }
            }
        }
    }
}
