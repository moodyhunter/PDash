import QtQuick
import QtQuick.Controls

import pd.mooody.me

RoundButton {
    id: root
    property int size: 50
    property color textcolor: AppTheme.text
    property color backgroundcolor: AppTheme.background
    property color bordercolor: AppTheme.highlight

    flat: true

    width: root.size
    height: root.size

    background: Rectangle {
        property real _colorratio: 1.2
        color: down ? Qt.darker(
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
