import QtQuick
import QtQuick.Controls
import QtGraphicalEffects

import pd.mooody.me

Item {
    id: root
    property int column: 0
    property int row: 0
    property int columnSpan: 1
    property int rowSpan: 1
    property bool hasHoveredAnimation: true

    clip: false

    HoverHandler {
        enabled: root.hasHoveredAnimation
        id: hoverhandler
    }

    DropShadow {
        id: shadow
        source: background
        anchors.fill: background
        transparentBorder: true
        color: Qt.lighter(AppTheme.highlight, 1.1)

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
        color: AppTheme.background
        border.color: AppTheme.border
        border.width: 1
        anchors.fill: parent
    }
}
