import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import pd.mooody.me as PD

import QtGraphicalEffects

ListView {
    model: PD.ActivityModel
    id: list
    Layout.fillHeight: true
    Layout.fillWidth: true
    Layout.rightMargin: 10
    ScrollBar.vertical: ScrollBar {
        policy: ScrollBar.AlwaysOn
    }
    clip: true
    spacing: 20
    delegate: PDPanel {
        implicitHeight: layout.implicitHeight + 30
        width: list.width - 20

        ColumnLayout {
            id: layout
            anchors.fill: parent
            anchors.margins: 15
            Label {
                color: PD.AppTheme.text
                Layout.fillWidth: true
                text: model.type
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            }
            Label {
                color: PD.AppTheme.text
                Layout.fillWidth: true
                text: model.title
                wrapMode: Text.WrapAnywhere
            }
            Label {
                color: PD.AppTheme.text
                Layout.fillWidth: true
                text: model.content
                wrapMode: Text.WrapAnywhere
            }
            Label {
                color: PD.AppTheme.text
                Layout.fillWidth: true
                text: model.date
                wrapMode: Text.WrapAnywhere
            }
        }
    }
}
