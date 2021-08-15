import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import QtGraphicalEffects

ColumnLayout {
    property var model
    property Component control

    id: root

    Text {
        color: Qt.darker(activeTheme.text, 1.5)
        text: qsTr("All activity")
        font.pointSize: 22
        Layout.fillWidth: true
    }

    ScrollView {
        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
        ScrollBar.vertical.policy: ScrollBar.AlwaysOn
        Layout.fillHeight: true
        Layout.fillWidth: true

        clip: true
        ListView {
            model: root.model
            spacing: 20
            anchors.fill: parent
            delegate: comp
        }

        Component {
            id: comp
            Item {
                width: parent.width
                implicitHeight: loader.implicitHeight + loader.anchors.margins * 2
                HoverHandler {
                    id: hover
                }
                DropShadow {
                    id: shadow
                    source: background
                    anchors.fill: background
                    transparentBorder: true
                    radius: 15
                }

                Rectangle {
                    id: background
                    radius: 0
                    color: hover.hovered ? activeTheme.handlerHoverColor : activeTheme.background
                    border.color: activeTheme.border
                    border.width: 1
                    anchors.fill: parent
                }

                Loader {
                    id: loader
                    anchors.fill: parent
                    anchors.margins: 10
                    property var modelData: root.model[index]
                    sourceComponent: control
                }
            }
        }
    }
}
