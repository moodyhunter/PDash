import QtQuick
import QtQuick.Layouts
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Shapes
import "components"

Window {
    width: 970
    height: 610
    visible: true
    title: qsTr("PD - The Personal Dashboard")
    id: rootWindow
    color: "#eeeeee"

    property bool editing: true

    SplitView {
        id: splitview
        anchors.fill: parent
        spacing: 40
        FixedGrid {
            id: grid
            SplitView.fillWidth: true
            columns: 20
            rows: 20
            columnSpacing: 10
            rowSpacing: 10
            model: [{
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
        }

        ColumnLayout {
            SplitView.maximumWidth: 500
            SplitView.minimumWidth: 150
            SplitView.preferredWidth: 250

            Rectangle {
                Layout.fillHeight: true
                Layout.fillWidth: true
                color: "grey"
            }

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
