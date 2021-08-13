import QtQuick
import QtQuick.Layouts
import QtQuick.Window
import "components"

Window {
    width: 970
    height: 610
    visible: true
    title: qsTr("PD - The Personal Dashboard")
    id: root
    color: "#eeeeee"

    RowLayout {
        anchors.fill: parent
        spacing: 40
        GridLayout {
            id: grid
            columnSpacing: 4
            rowSpacing: 10
            columns: 20
            rows: 20

            Repeater {
                model: [1, 2, 3, 4, 5, 6, 7]
                PDPanel {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.rowSpan: 3
                }
            }
        }

        ColumnLayout {
            PDPanel {
                Layout.fillHeight: true
                Layout.fillWidth: true
                hasHoveredAnimation: false
            }
        }
    }
}
