import QtQuick

import PDPlugins.Clock

Item {
    Text {
        anchors.fill: parent
        text: qsTr("This is PD Clock") + ClockProp.val
    }
}
