import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import pd.mooody.me

Popup {
    id: root

    property string componentType

    readonly property int _paddingH: root.width / 2 - 250
    readonly property int _paddingV: root.height / 2 - 200

    bottomPadding: _paddingV
    topPadding: _paddingV
    leftPadding: _paddingH
    rightPadding: _paddingH

    parent: Overlay.overlay
    width: parent.width
    height: parent.height
    closePolicy: Popup.NoAutoClose
    modal: true

    signal itemSelected(string itemType)

    background: Rectangle {
        color: "transparent"
    }

    contentItem: PDGlowedRectangle {
        hoverEnabled: false
        ListView {
            anchors.fill: parent
            model: PanelModel.getQmlInfoFromType(root.componentType).properties
            delegate: ColumnLayout {
                Text {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    text: modelData
                }
            }
        }
    }
}
