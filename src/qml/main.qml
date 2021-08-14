import QtQuick
import QtQuick.Layouts
import QtQuick.Window
import QtQuick.Controls
import "components"

Window {
    width: 970
    height: 610
    visible: true
    title: qsTr("PD - The Personal Dashboard")
    id: root
    color: "#eeeeee"

    SplitView {
        anchors.fill: parent
        spacing: 40
        GridLayout {
            id: grid
            SplitView.fillWidth: true
            columnSpacing: 4
            rowSpacing: 10
            columns: 20
            rows: 20

            Repeater {
                model: [1, 2, 3, 4, 5, 6, 7]
                PDPanel {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.row: Math.random()*20
                    Layout.column: Math.random()*20
                }
            }
        }

        ColumnLayout {
            SplitView.maximumWidth: 500
            SplitView.minimumWidth: 150
            SplitView.preferredWidth: 250

            PDPanel {
                Layout.fillHeight: true
                Layout.fillWidth: true
                hasHoveredAnimation: false
            }
        }
    }
}
