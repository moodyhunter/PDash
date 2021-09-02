import QtQuick
import QtQuick.Layouts

import pd.mooody.me

Item {
    id: root
    property var model: PanelModel
    property alias totalRows: baseGrid.rows
    property alias totalColumns: baseGrid.columns
    property alias rowSpacing: baseGrid.rowSpacing
    property alias columnSpacing: baseGrid.columnSpacing

    property bool editMode: false
    property PDPanel current: null

    GridLayout {
        columns: 20
        rows: 20
        columnSpacing: 15
        rowSpacing: 15
        id: baseGrid
        z: -1
        anchors.fill: parent
        implicitHeight: 150
        implicitWidth: 150

        property real columnWidth: (baseGrid.width - columnSpacing
                                    * (baseGrid.columns - 1)) / baseGrid.columns
        property real rowHeight: (baseGrid.height - rowSpacing
                                  * (baseGrid.rows - 1)) / baseGrid.rows

        Repeater {
            id: repeater
            model: baseGrid.rows * baseGrid.columns
            delegate: Item {
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.row: Math.floor(index / baseGrid.rows)
                Layout.column: index % baseGrid.columns
            }
        }
    }

    Repeater {
        parent: root
        model: root.model
        PDPanel {
            z: 10
            hasHoveredAnimation: true
            parent: root

            MouseArea {
                visible: editMode
                hoverEnabled: true
                anchors.fill: parent
                onEntered: {
                    current = parent
                    if (editMode) {
                        syncSizeHandleSizes()
                    }
                }
                onReleased: if (editMode)
                                syncSizeHandleSizes()
            }

            property var _model: model

            property int cid: model.row * totalColumns + model.column
            x: baseGrid.children[cid].x
            y: baseGrid.children[cid].y
            width: model.columnSpan * (baseGrid.columnWidth + columnSpacing) - columnSpacing
            height: model.rowSpan * (baseGrid.rowHeight + rowSpacing) - rowSpacing

            function syncSizeHandleSizes() {
                sizehandle._start.x = x / sizehandle.parent.width
                sizehandle._start.y = y / sizehandle.parent.height
                sizehandle._end.x = (x + width) / sizehandle.parent.width
                sizehandle._end.y = (y + height) / sizehandle.parent.height
            }
        }
    }

    RectangleAreaHandle {
        id: sizehandle
        z: 99
        visible: editMode && current != null
        reverseAllowed: false
        anchors.fill: parent
        handleSize: 20

        property int centerX
        property int centerY

        Text {
            color: AppTheme.text
            id: sizeLabel
            visible: parent.visible
            x: current == null ? 0 : current.x + current.width / 2 - width / 2
            y: current == null ? 0 : current.y + current.height / 2 - height / 2
            text: current == null ? "N/A" : "x = " + current._model.column
                                    + ", y = " + current._model.row + "\nSize: "
                                    + current._model.columnSpan + "x" + current._model.rowSpan
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }

        onReleased: current.syncSizeHandleSizes()
        onMoved: function (start, end) {
            if (!current)
                return

            current._model.column = Math.round(
                        realStartX / (baseGrid.columnWidth + columnSpacing))
            current._model.row = Math.round(
                        realStartY / (baseGrid.rowHeight + rowSpacing))
            current._model.columnSpan = Math.round(
                        (realEndX - realStartX) / (baseGrid.columnWidth + columnSpacing))
            current._model.rowSpan = Math.round(
                        (realEndY - realStartY) / (baseGrid.rowHeight + rowSpacing))
        }
    }
}
