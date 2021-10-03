import QtQuick
import QtQuick.Layouts

import PDPlugins.Clock
import pd.mooody.me

Clock {
    PDLabel {
        anchors.fill: parent
        id: currentTime
        fontSizeMode: Text.Fit
        font.pixelSize: 72
    }
    Timer {
        running: true
        interval: 500
        repeat: true
        triggeredOnStart: true
        onTriggered: {
            var date = new Date()
            currentTime.text = date.toLocaleString(Qt.locale(),
                                                   parent.formatString)
        }
    }
}
