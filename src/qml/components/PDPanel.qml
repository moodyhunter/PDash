import QtQuick
import QtQuick.Controls

import QtGraphicalEffects

Item {
    id: root
    property int column
    property int columnSpan: 1
    property int row
    property int rowSpan: 1
    property bool hasHoveredAnimation: true

    clip: false

    HoverHandler {
        enabled: hasHoveredAnimation
        id: hoverhandler
    }

    DropShadow {
        id: shadow
        source: background
        anchors.fill: background
        transparentBorder: true
        color: Qt.lighter(activeTheme.highlight, 1.1)

        Behavior on radius {
            animation: NumberAnimation {
                easing.type: Easing.OutCirc
                duration: 270
            }
        }

        state: hoverhandler.hovered ? "HOVERED" : "NORMAL"

        states: [
            State {
                name: "HOVERED"
                PropertyChanges {
                    target: shadow
                    radius: 30
                }
            },
            State {
                name: "NORMAL"
                PropertyChanges {
                    target: shadow
                    radius: 5
                }
            }
        ]
    }

    Rectangle {
        id: background
        radius: 16
        color: activeTheme.background
        border.color: activeTheme.border
        border.width: 1
        anchors.fill: parent
    }
}
