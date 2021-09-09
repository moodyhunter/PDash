import QtQuick
import QtQuick.Layouts

import pd.mooody.me

Item {
    id: root
    property int totalRows: 20
    property int totalColumns: 20
    property int rowSpacing: 15
    property int columnSpacing: 15

    property bool editMode: false
    property PDPanelCard selectedPanel: null
    property bool itemMoving: false

    function syncSizeHandleSizes() {
        sizehandle._start.x = selectedPanel.x / sizehandle.parent.width
        sizehandle._start.y = selectedPanel.y / sizehandle.parent.height
        sizehandle._end.x = (selectedPanel.x + selectedPanel.width) / sizehandle.parent.width
        sizehandle._end.y = (selectedPanel.y + selectedPanel.height) / sizehandle.parent.height
    }

    GridLayout {
        id: baseGrid
        anchors.fill: parent

        rows: totalRows
        columns: totalColumns
        columnSpacing: root.columnSpacing
        rowSpacing: root.rowSpacing

        z: -1

        property real columnWidth: (width - columnSpacing * (columns - 1)) / columns
        property real rowHeight: (height - rowSpacing * (rows - 1)) / rows

        Repeater {
            model: totalRows * totalColumns
            delegate: Item {
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.row: Math.floor(index / totalRows)
                Layout.column: index % totalColumns
            }
        }
    }

    Repeater {
        id: repeater
        model: PanelModel
        PDPanelCard {
            z: 10
            hasHoveredAnimation: true
            parent: root

            MouseArea {
                id: mouse
                visible: editMode
                hoverEnabled: true
                anchors.fill: parent
                onEntered: {
                    if (!itemMoving) {
                        selectedPanel = parent
                        if (editMode) {
                            syncSizeHandleSizes()
                        }
                    }
                }
            }

            property var _model: model
            property var _index: index
            property int cid: model.row * totalColumns + model.column

            x: baseGrid.children[cid].x
            y: baseGrid.children[cid].y
            width: model.columnSpan * (baseGrid.columnWidth + columnSpacing) - columnSpacing
            height: model.rowSpan * (baseGrid.rowHeight + rowSpacing) - rowSpacing
        }
    }

    RectangleAreaHandle {
        id: sizehandle
        z: 99
        visible: editMode && selectedPanel != null
        reverseAllowed: false
        anchors.fill: parent
        handleSize: 20

        property int centerX
        property int centerY

        Column {
            x: selectedPanel == null ? 0 : selectedPanel.x + selectedPanel.width
                                       / 2 - implicitWidth / 2
            y: selectedPanel == null ? 0 : selectedPanel.y + selectedPanel.height
                                       / 2 - implicitHeight / 2
            spacing: 10
            id: column
            Text {
                anchors.horizontalCenter: column.horizontalCenter
                color: AppTheme.text
                visible: parent.visible
                text: (selectedPanel == null || selectedPanel._model
                       === null) ? "N/A" : "x = " + selectedPanel._model.column
                                   + ", y = " + selectedPanel._model.row
                                   + "\nSize: " + selectedPanel._model.columnSpan
                                   + "x" + selectedPanel._model.rowSpan
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }
            CircularButton {
                text: qsTr("Delete")
                anchors.horizontalCenter: column.horizontalCenter
                onClicked: PanelModel.removeItem(selectedPanel._index)
            }
        }

        onReleased: {
            itemMoving = false
            syncSizeHandleSizes()
        }
        onMoved: function (start, end) {
            if (!selectedPanel)
                return

            if (!itemMoving)
                itemMoving = true

            selectedPanel._model.column = Math.round(
                        sizehandle.realStartX / (baseGrid.columnWidth + columnSpacing))
            selectedPanel._model.row = Math.round(
                        sizehandle.realStartY / (baseGrid.rowHeight + rowSpacing))
            selectedPanel._model.columnSpan = Math.round(
                        (sizehandle.realEndX - sizehandle.realStartX)
                        / (baseGrid.columnWidth + columnSpacing))
            selectedPanel._model.rowSpan = Math.round(
                        (sizehandle.realEndY - sizehandle.realStartY)
                        / (baseGrid.rowHeight + rowSpacing))
        }
    }

    CircularButton {
        id: editButton
        z: 99
        backgroundcolor: editMode ? AppTheme.highlight : AppTheme.background
        textcolor: editMode ? AppTheme.background : AppTheme.highlight
        anchors.margins: 10
        anchors.right: root.right
        anchors.bottom: root.bottom
        text: qsTr("Edit")
        onClicked: {
            if (editMode)
                PanelModel.saveToDatabase()
            editMode = !editMode
        }
    }

    CircularButton {
        z: 99
        id: addButton
        anchors.right: editButton.left
        anchors.bottom: root.bottom
        anchors.margins: 10
        text: qsTr("Add")
        state: editMode ? "visible" : "hidden"
        states: [
            State {
                name: "visible"
                PropertyChanges {
                    target: addButton
                    opacity: 1
                }
            },
            State {
                name: "hidden"
                PropertyChanges {
                    target: addButton
                    opacity: 0
                }
            }
        ]
        transitions: [
            Transition {
                reversible: true
                PropertyAnimation {
                    easing.type: Easing.InQuad
                    properties: "opacity"
                    duration: 200
                }
            }
        ]
        onClicked: {
            PanelModel.appendItem({
                                      "row": 2,
                                      "column": 2,
                                      "rowSpan": 4,
                                      "columnSpan": 4
                                  })
        }
    }
}
