import QtQuick
import QtQuick.Layouts

import PDPlugins.Clock
import pd.mooody.me

Clock {
    id: clock

    PDLabel {
        anchors.fill: parent
        id: currentTime
        fontSizeMode: clock.autoSize ? Text.Fit : Text.FixedSize
        font.pixelSize: clock.autoSize ? 75 : clock.fontSize
    }

    Timer {
        running: true
        interval: 500
        repeat: true
        triggeredOnStart: true
        onTriggered: currentTime.text = clock.prefix
                     + (clock.prefixSpace ? " " : "") + new Date().toLocaleString(
                         Qt.locale(),
                         clock.formatString) + (clock.suffixSpace ? " " : "") + clock.suffix
    }
}
