import QtQuick
import QtQuick.Layouts
import pd.mooody.me

import PDPlugins.Clock

Clock {
    anchors.fill: parent
    PDLabel {
        anchors.fill: parent
        id: currentTime
        fontSizeMode: Text.Fit
        //        minimumPixelSize: 10
        font.pixelSize: 72
    }
    Timer {
        running: true
        interval: 500
        triggeredOnStart: true
        onTriggered: {
            var date = new Date()
            var txt = date.toTimeString() + " - " + date.toLocaleDateString(
                        Qt.locale(), "dddd MMMM d yyyy")
            currentTime.text = txt
            restart()
        }
    }
}
