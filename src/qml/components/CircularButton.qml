import QtQuick
import QtQuick.Controls

RoundButton {
    id: root
    property int size: 50
    property color textcolor: activeTheme.text
    property color backgroundcolor: activeTheme.background
    property color bordercolor: activeTheme.highlight

    flat: true

    width: root.size
    height: root.size

    background: Rectangle {
        property real _colorratio: 1.5
        color: down ? Qt.darker(
                          root.backgroundcolor,
                          _colorratio) : (hovered ? Qt.lighter(
                                                        root.backgroundcolor,
                                                        _colorratio) : root.backgroundcolor)
        anchors.fill: root
        radius: root.size
        border.width: 1
        border.color: root.bordercolor
    }
}
