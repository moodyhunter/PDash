import QtQuick

import PDPlugins.Clock as Clock

Item {
    Text {
        anchors.fill: parent
        text: qsTr("This is PD Clock: ") + Clock.ClockProp.val
        font.bold: true
        font.italic: true
        font.underline: true
        font.strikeout: true
        font.pointSize: 10
        horizontalAlignment: Text.AlignHCenter
        styleColor: "#27e024"
        style: Text.Raised
        color: "#ff0000"
    }
}
