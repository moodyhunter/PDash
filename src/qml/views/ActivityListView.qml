import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtGraphicalEffects

import pd.mooody.me

ListView {
    model: ActivityModel
    id: list
    Layout.fillHeight: true
    Layout.fillWidth: true
    Layout.rightMargin: 10
    ScrollBar.vertical: ScrollBar {
        policy: ScrollBar.AlwaysOn
    }
    clip: true
    spacing: 20
    delegate: PDPanelCard {
        implicitHeight: layout.implicitHeight + 30
        width: list.width - 20

        ColumnLayout {
            id: layout
            anchors.fill: parent
            anchors.margins: 15
            Label {
                color: AppTheme.text
                Layout.fillWidth: true
                text: model.type
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            }
            Label {
                color: AppTheme.text
                Layout.fillWidth: true
                text: model.title
                wrapMode: Text.WrapAnywhere
            }
            Label {
                color: AppTheme.text
                Layout.fillWidth: true
                text: model.content
                wrapMode: Text.WrapAnywhere
            }
            Label {
                color: AppTheme.text
                Layout.fillWidth: true
                text: model.date
                wrapMode: Text.WrapAnywhere
            }
        }
    }
}
