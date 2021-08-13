import QtQuick
import QtQuick.Controls

import QtGraphicalEffects

Item {
    property bool hasHoveredAnimation: true
    clip: false

    Rectangle {
        id: background
        radius: 20
        color: "#fafafa"
        border.color: "black"
        border.width: 1
        anchors.fill: parent
    }

    DropShadow {
        id: shadow
        source: background
        anchors.fill: background
        transparentBorder: true
        state: hasHoveredAnimation
               && hoverhandler.hovered ? "HOVERED" : "NORMAL"

        Behavior on radius {
            animation: NumberAnimation {
                easing.type: Easing.OutCirc
                duration: 270
            }
        }

        HoverHandler {
            id: hoverhandler
        }
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
}
