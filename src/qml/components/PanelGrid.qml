import QtQuick
import QtQuick.Layouts

import pd.mooody.me

Item {
    id: root
    property list<PanelModel> model
    property alias rows: gridlayout.rows
    property alias columns: gridlayout.columns
    property alias rowSpacing: gridlayout.rowSpacing
    property alias columnSpacing: gridlayout.columnSpacing

    property bool editMode: false
    property PDPanel current: null
    property list<PDPanel> panels

    GridLayout {
        columns: 20
        rows: 20
        columnSpacing: 15
        rowSpacing: 15
        z: -1
        anchors.fill: parent
        id: gridlayout
        implicitHeight: 150
        implicitWidth: 150

        property real columnWidth: (gridlayout.width - columnSpacing
                                    * (gridlayout.columns - 1)) / gridlayout.columns
        property real rowHeight: (gridlayout.height - rowSpacing
                                  * (gridlayout.rows - 1)) / gridlayout.rows

        Repeater {
            id: repeater
            model: gridlayout.rows * gridlayout.columns
            delegate: Item {
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.row: Math.floor(index / gridlayout.rows)
                Layout.column: index % gridlayout.columns
            }
        }
    }

    function getPositions() {
        var r = []
        for (var i = 0; i < panels.length; i++) {
            var obj = {
                "row": panels[i].row,
                "column": panels[i].column,
                "rowSpan": panels[i].rowSpan,
                "columnSpan": panels[i].columnSpan
            }
            r.push(obj)
        }
        return JSON.stringify(r)
    }

    function loadFromModel() {
        for (var d = 0; d < panels.length; d++) {
            panels[d].destroy()
        }

        panels = []

        for (var i = 0; i < root.model.length; ++i) {
            var p = comp.createObject(root)
            if (p !== null) {
                panels.push(p)
                p.row = model[i].row
                p.column = model[i].column
                p.columnSpan = model[i].columnSpan
                p.rowSpan = model[i].rowSpan
            }
        }
    }

    Component.onCompleted: {
        loadFromModel()
    }

    Component {
        id: comp
        PDPanel {
            z: 10
            hasHoveredAnimation: true
            property int childIndex: row * columns + column
            parent: root
            x: gridlayout.children[childIndex].x
            y: gridlayout.children[childIndex].y
            width: columnSpan * (gridlayout.columnWidth + columnSpacing) - columnSpacing
            height: rowSpan * (gridlayout.rowHeight + rowSpacing) - rowSpacing

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
            text: current == null ? "N/A" : "x = " + current.column + ", y = " + current.row
                                    + "\nSize: " + current.columnSpan + "x" + current.rowSpan
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }

        onReleased: current.syncSizeHandleSizes()
        onMoved: function (start, end) {
            if (!current)
                return

            current.column = Math.round(
                        realStartX / (gridlayout.columnWidth + columnSpacing))
            current.row = Math.round(
                        realStartY / (gridlayout.rowHeight + rowSpacing))
            current.columnSpan = Math.round(
                        (realEndX - realStartX) / (gridlayout.columnWidth + columnSpacing))
            current.rowSpan = Math.round(
                        (realEndY - realStartY) / (gridlayout.rowHeight + rowSpacing))
        }
    }
}
