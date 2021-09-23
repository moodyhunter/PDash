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
        color: textcolor
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    background: Rectangle {
        readonly property real _colorratio: 1.2
        color: root.down ? Qt.darker(
                               root.backgroundcolor,
                               _colorratio) : (root.hovered ? Qt.lighter(
                                                                  root.backgroundcolor,
                                                                  _colorratio) : root.backgroundcolor)
        anchors.fill: root
        radius: root.size
        border.width: 1
        border.color: root.bordercolor
    }
}
