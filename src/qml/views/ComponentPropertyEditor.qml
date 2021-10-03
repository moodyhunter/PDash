import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import pd.mooody.me

Popup {
    id: root

    signal editFinished

    property string componentType

    function setComponentProperties(props) {
        propModel.setCurrentPropertyValues(props)
    }

    readonly property int _paddingH: root.width / 2 - 250
    readonly property int _paddingV: root.height / 2 - 200

    bottomPadding: _paddingV
    topPadding: _paddingV
    leftPadding: _paddingH
    rightPadding: _paddingH

    parent: Overlay.overlay
    width: parent.width
    height: parent.height
    closePolicy: Popup.CloseOnEscape
    modal: true

    background: Rectangle {
        color: "transparent"
    }

    PluginComponentPropertyModel {
        id: propModel
        componentType: root.componentType
    }

    contentItem: PDGlowedRectangle {
        hoverEnabled: false
        ListView {
            anchors.fill: parent
            anchors.margins: 10
            model: propModel
            delegate: ColumnLayout {
                RowLayout {
                    Layout.fillWidth: true
                    PDLabel {
                        Layout.fillHeight: true
                        text: name
                    }
                    PDLabel {
                        Layout.fillHeight: true
                        text: description
                    }
                    PDLabel {
                        Layout.fillHeight: true
                        text: value
                    }
                }
            }
        }
    }
}
