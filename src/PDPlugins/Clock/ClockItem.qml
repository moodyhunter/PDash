import QtQuick

import PDPlugins.Clock as Clock

Item {
    Text {
        anchors.fill: parent
        text: qsTr("This is PD Clock") + Clock.ClockProp.val
    }
}
