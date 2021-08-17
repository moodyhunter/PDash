import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import QtGraphicalEffects

ListView {
    property Component control
    id: list
    Layout.fillHeight: true
    Layout.fillWidth: true
    Layout.rightMargin: 10
    ScrollBar.vertical: ScrollBar {
        policy: ScrollBar.AlwaysOn
    }
    clip: true
    spacing: 20
    delegate: PDPanel {
        implicitHeight: loader.implicitHeight + loader.anchors.margins * 2
        width: list.width - 20

        Loader {
            id: loader
            anchors.fill: parent
            anchors.margins: 15
            property var modelData: list.model[index]
            sourceComponent: control
        }
    }
}
