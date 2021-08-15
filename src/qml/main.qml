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
    color: "#eeeeee"

    property bool editing: true

    property var panelModel: [{
            "row": 3,
            "column": 2,
            "rowSpan": 7,
            "columnSpan": 16
        }, {
            "row": 10,
            "column": 2,
            "rowSpan": 7,
            "columnSpan": 8
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

    Drawer {
        width: 0.23 * rootWindow.width
        height: rootWindow.height
        Label {
            text: "Content goes here!"
            anchors.centerIn: parent
        }
    }

    SplitView {
        anchors.fill: parent
        id: splitview
        spacing: 40

        handle: Rectangle {
            color: SplitHandle.pressed ? "#959595" : (SplitHandle.hovered ? "#b6b6b6" : "#dedede")
            implicitWidth: 5
            radius: 5
        }

        PanelGrid {
            id: grid
            SplitView.fillWidth: true
            columns: 20
            rows: 20
            columnSpacing: 15
            rowSpacing: 15
            model: panelModel
        }

        ColumnLayout {
            SplitView.maximumWidth: 500
            SplitView.minimumWidth: 150
            SplitView.preferredWidth: 350

            ActivityListView {
                model: activityStreamModel
                Layout.fillWidth: true
                Layout.fillHeight: true
            }

            RowLayout {
                Button {
                    text: "Toggle Edit Mode"
                    onClicked: grid.editMode = !grid.editMode
                }

                Button {
                    text: "Get Item Sizes"
                    onClicked: console.log(grid.getPositions())
                }
            }
        }
    }
}
