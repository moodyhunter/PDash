import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import pd.mooody.me

ListView {
    model: ActivityModel
    id: list
    Layout.fillHeight: true
    Layout.fillWidth: true
    Layout.rightMargin: 10
    ScrollBar.vertical: ScrollBar {
        policy: ScrollBar.AlwaysOn
    }
    spacing: 20
    boundsBehavior: Flickable.StopAtBounds
    delegate: PDGlowedRectangle {
        implicitHeight: layout.implicitHeight + 30
        width: list.width - 20

        ColumnLayout {
            id: layout
            anchors.fill: parent
            anchors.margins: 15
            PDLabel {
                Layout.fillWidth: true
                text: type
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            }
            PDLabel {
                Layout.fillWidth: true
                text: title
                wrapMode: Text.WrapAnywhere
            }
            PDLabel {
                Layout.fillWidth: true
                text: content
                wrapMode: Text.WrapAnywhere
            }
            PDLabel {
                Layout.fillWidth: true
                text: date
                wrapMode: Text.WrapAnywhere
            }
        }
    }
}
