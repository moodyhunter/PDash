import QtQuick
import pd.mooody.me

Window {
    id: rootWindow
    color: AppTheme.dark
    width: 1300
    height: 700
    visible: true
    title: qsTr("PD - The Personal Dashboard")
    MainComponent {
        anchors.fill: parent
    }
}
