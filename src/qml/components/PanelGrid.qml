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

    GridLayout {
        id: baseGrid
        anchors.fill: parent

        columns: root.totalColumns
        rows: root.totalRows
        columnSpacing: root.columnSpacing
        rowSpacing: root.rowSpacing

        z: -1

        property real columnWidth: (width - columnSpacing * (columns - 1)) / columns
        property real rowHeight: (height - rowSpacing * (rows - 1)) / rows

        Repeater {
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
        model: PanelModel
        PDPanelCard {
            z: 10
            hasHoveredAnimation: true
            parent: root

            MouseArea {
                visible: editMode
                hoverEnabled: true
                anchors.fill: parent
                onEntered: {
                    selectedPanel = parent
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
        visible: editMode && selectedPanel != null
        reverseAllowed: false
        anchors.fill: parent
        handleSize: 20

        property int centerX
        property int centerY

        Text {
            color: AppTheme.text
            id: sizeLabel
            visible: parent.visible
            x: selectedPanel == null ? 0 : selectedPanel.x + selectedPanel.width / 2 - width / 2
            y: selectedPanel == null ? 0 : selectedPanel.y + selectedPanel.height / 2 - height / 2
            text: selectedPanel == null ? "N/A" : "x = " + selectedPanel._model.column
                                          + ", y = " + selectedPanel._model.row
                                          + "\nSize: " + selectedPanel._model.columnSpan
                                          + "x" + selectedPanel._model.rowSpan
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }

        onReleased: selectedPanel.syncSizeHandleSizes()
        onMoved: function (start, end) {
            if (!selectedPanel)
                return

            selectedPanel._model.column = Math.round(
                        realStartX / (baseGrid.columnWidth + columnSpacing))
            selectedPanel._model.row = Math.round(
                        realStartY / (baseGrid.rowHeight + rowSpacing))
            selectedPanel._model.columnSpan = Math.round(
                        (realEndX - realStartX) / (baseGrid.columnWidth + columnSpacing))
            selectedPanel._model.rowSpan = Math.round(
                        (realEndY - realStartY) / (baseGrid.rowHeight + rowSpacing))
        }
    }

    CircularButton {
        z: 99
        backgroundcolor: editMode ? AppTheme.highlight : AppTheme.background
        textcolor: editMode ? AppTheme.background : AppTheme.highlight
        anchors.margins: 10
        anchors.right: root.right
        anchors.bottom: root.bottom
        text: "Edit"
        onClicked: editMode = !editMode
    }
}
