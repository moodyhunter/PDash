import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import QtGraphicalEffects

ScrollView {
    property var model

    id: root
    ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
    ScrollBar.vertical.policy: ScrollBar.AlwaysOn

    ListView {
        model: root.model
        spacing: 20
        Layout.margins: 10

        delegate: Item {
            clip: false
            width: root.width
            height: clayout.implicitHeight
            Rectangle {
                id: content
                color: "#f6f6f6"
                radius: 10
                anchors.fill: parent
                ColumnLayout {
                    id: clayout
                    anchors.fill: parent
                    Text {
                        text: modelData.type
                    }
                    Text {
                        text: modelData.title
                    }
                    Text {
                        text: modelData.id
                    }
                    Text {
                        text: modelData.text
                    }
                    Text {
                        text: modelData.date
                    }
                }
            }

            DropShadow {
                anchors.fill: content
                source: content
                transparentBorder: true
                radius: 10
                verticalOffset: 2
                horizontalOffset: 2
            }
        }
    }
}
