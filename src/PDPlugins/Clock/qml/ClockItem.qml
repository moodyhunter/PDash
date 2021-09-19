import QtQuick
import QtQuick.Layouts
import pd.mooody.me

import PDPlugins.Clock

Clock {
    PDLabel {
        id: currentTime
    }
    Timer {
        running: true
        interval: 1000
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
