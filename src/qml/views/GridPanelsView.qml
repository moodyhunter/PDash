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
    property PDGlowedRectangle selectedPanel: null
    property bool itemMoving: false

    function syncSizeHandleSizes() {
        sizehandle._start.x = root.selectedPanel.x / root.width
        sizehandle._start.y = root.selectedPanel.y / root.height
        sizehandle._end.x = (root.selectedPanel.x + root.selectedPanel.width) / root.width
        sizehandle._end.y = (root.selectedPanel.y + root.selectedPanel.height) / root.height
    }

    GridLayout {
        id: baseGrid
        anchors.fill: parent

        rows: root.totalRows
        columns: root.totalColumns
        columnSpacing: root.columnSpacing
        rowSpacing: root.rowSpacing

        z: -1

        property real columnWidth: (width - columnSpacing * (columns - 1)) / columns
        property real rowHeight: (height - rowSpacing * (rows - 1)) / rows

        Repeater {
            model: root.totalRows * root.totalColumns
            delegate: Item {
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.row: Math.floor(index / root.totalRows)
                Layout.column: index % root.totalColumns
            }
        }
    }

    Repeater {
        id: repeater
        model: PanelModel
        PDGlowedRectangle {
            id: panelRectangle
            z: 10
            hoverEnabled: true
            parent: root

            property var _model: model
            property var _index: index
            property int cid: model.row * root.totalColumns + model.column

            Loader {
                Component {
                    id: unknownComponentErrorComponent
                    PDLabel {
                        anchors.fill: parent
                        text: qsTr("Unknown Plugin Component") + "\n'"
                              + panelRectangle._model.contentType + "'"
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                    }
                }

                id: _loader
                clip: true
                anchors.fill: parent
                anchors.margins: 10
                Component.onCompleted: {
                    var qmlTypeInfo = PanelModel.getQmlInfoFromType(
                                parent._model.contentType)
                    if (qmlTypeInfo.qmlPath === "") {
                        _loader.sourceComponent = unknownComponentErrorComponent
                    } else {
                        _loader.setSource(qmlTypeInfo.qmlPath,
                                          qmlTypeInfo.initialProperties)
                    }
                }
            }

            x: baseGrid.children[cid].x
            y: baseGrid.children[cid].y
            width: model.columnSpan * (baseGrid.columnWidth + root.columnSpacing)
                   - root.columnSpacing
            height: model.rowSpan * (baseGrid.rowHeight + root.rowSpacing) - root.rowSpacing

            MouseArea {
                id: mouse
                visible: root.editMode
                hoverEnabled: true
                anchors.fill: parent
                onEntered: {
                    if (!root.itemMoving) {
                        root.selectedPanel = parent
                        if (root.editMode) {
                            root.syncSizeHandleSizes()
                        }
                    }
                }
            }
        }
    }

    RectangleAreaHandle {
        id: sizehandle
        z: 99
        visible: root.editMode && root.selectedPanel != null
        reverseAllowed: false
        anchors.fill: parent
        handleSize: 20

        ColumnLayout {
            x: root.selectedPanel == null ? 0 : root.selectedPanel.x
                                            + root.selectedPanel.width / 2 - implicitWidth / 2
            y: root.selectedPanel == null ? 0 : root.selectedPanel.y + root.selectedPanel.height
                                            / 2 - implicitHeight / 2
            spacing: 10
            Text {
                Layout.fillWidth: true
                color: AppTheme.text
                visible: parent.visible
                text: (root.selectedPanel == null || root.selectedPanel._model
                       === null) ? "N/A" : "x = " + root.selectedPanel._model.column
                                   + ", y = " + root.selectedPanel._model.row
                                   + "\nSize: " + root.selectedPanel._model.columnSpan
                                   + "x" + root.selectedPanel._model.rowSpan
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }

            RowLayout {
                CircularButton {
                    Layout.fillHeight: true
                    text: qsTr("Edit")
                    onClicked: {
                        pluginPropertyEditor.componentType = root.selectedPanel._model.contentType
                        pluginPropertyEditor.open()
                    }
                }
                CircularButton {
                    Layout.fillHeight: true
                    text: qsTr("Delete")
                    textcolor: AppTheme.warn
                    onClicked: PanelModel.removeItem(root.selectedPanel._index)
                }
            }
        }

        onReleased: {
            root.itemMoving = false
            root.syncSizeHandleSizes()
        }

        onMoved: function (start, end) {
            if (!root.selectedPanel)
                return

            if (!root.itemMoving)
                root.itemMoving = true

            root.selectedPanel._model.column = Math.round(
                        sizehandle.realStartX / (baseGrid.columnWidth + root.columnSpacing))
            root.selectedPanel._model.row = Math.round(
                        sizehandle.realStartY / (baseGrid.rowHeight + root.rowSpacing))
            root.selectedPanel._model.columnSpan = Math.round(
                        (sizehandle.realEndX - sizehandle.realStartX)
                        / (baseGrid.columnWidth + root.columnSpacing))
            root.selectedPanel._model.rowSpan = Math.round(
                        (sizehandle.realEndY - sizehandle.realStartY)
                        / (baseGrid.rowHeight + root.rowSpacing))
        }
    }

    CircularButton {
        z: 99
        id: editButton
        backgroundcolor: root.editMode ? AppTheme.highlight : AppTheme.background
        textcolor: root.editMode ? AppTheme.background : AppTheme.highlight
        anchors.margins: 10
        anchors.right: root.right
        anchors.bottom: root.bottom
        text: qsTr("Edit")
        onClicked: {
            if (root.editMode)
                PanelModel.saveToDatabase()
            root.editMode = !root.editMode
        }
    }

    CircularButton {
        z: 99
        id: addButton
        anchors.right: editButton.left
        anchors.bottom: root.bottom
        anchors.margins: 10
        text: qsTr("Add")
        state: root.editMode ? "visible" : "hidden"
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
            pluginTypeSelector.open()
        }
    }

    PluginTypeView {
        id: pluginTypeSelector
        onItemSelected: function (type) {
            PanelModel.appendItem({
                                      "row": 2,
                                      "column": 2,
                                      "rowSpan": 4,
                                      "columnSpan": 4,
                                      "contentType": type,
                                      "contentData": ""
                                  })
            pluginTypeSelector.close()
        }
    }

    ComponentPropertyEditor {
        id: pluginPropertyEditor
    }
}
