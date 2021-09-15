import QtQuick
import QtQuick.Controls
import QtGraphicalEffects

import pd.mooody.me

Control {
    id: root
    clip: false
    hoverEnabled: true

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

        state: root.hovered ? "HOVERED" : "NORMAL"

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
