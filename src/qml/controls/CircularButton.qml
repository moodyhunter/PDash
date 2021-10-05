import QtQuick
import QtQuick.Templates as T

import pd.mooody.me

T.RoundButton {
    id: root
    property int size: 50
    property color textcolor: AppTheme.text
    property color backgroundcolor: AppTheme.background
    property color bordercolor: AppTheme.highlight

    flat: true
    width: root.size
    height: root.size

    contentItem: Text {
        text: root.text
        color: root.textcolor
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    background: Rectangle {
        color: if (root.down)
                   return Qt.darker(root.backgroundcolor, 1.2)
               else if (root.hovered)
                   return Qt.lighter(root.backgroundcolor, 1.2)
               else
                   return root.backgroundcolor

        radius: root.size
        anchors.fill: root
        border.width: 1
        border.color: root.bordercolor
    }
}
