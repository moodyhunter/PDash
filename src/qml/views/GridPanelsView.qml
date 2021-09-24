import QtQuick
import QtQuick.Layouts

import pd.mooody.me

Item {
    id: root
    property int totalRows: 30
    property int totalColumns: 30
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

    Item {
        id: baseGrid
        anchors.fill: parent

        z: -1

        property real columnWidth: (baseGrid.width - root.columnSpacing
                                    * (root.totalColumns - 1)) / root.totalColumns
        property real rowHeight: (baseGrid.height - root.rowSpacing
                                  * (root.totalRows - 1)) / root.totalRows

        Repeater {
            id: repeater
            model: PanelModel
            PDGlowedRectangle {
                parent: baseGrid
                hoverEnabled: true
                id: panelRectangle

                x: (baseGrid.columnWidth + root.columnSpacing) * model.column
                y: (baseGrid.rowHeight + root.rowSpacing) * model.row
                z: 10
                width: (baseGrid.columnWidth + root.columnSpacing)
                       * model.columnSpan - root.columnSpacing
                height: (baseGrid.rowHeight + root.rowSpacing) * model.rowSpan - root.rowSpacing

                property var _model: model
                property var itemIndex: index

                Loader {
                    Component {
                        id: unknownComponentErrorComponent
                        PDLabel {
                            color: AppTheme.warn
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
                    onClicked: PanelModel.removeItem(
                                   root.selectedPanel.itemIndex)
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

            var newX = sizehandle.realStartX
            var newY = sizehandle.realStartY

            var newWidth = sizehandle.realEndX - sizehandle.realStartX
            var newHeight = sizehandle.realEndY - sizehandle.realStartY

            var tmpVSize = baseGrid.rowHeight + root.rowSpacing
            var tmpHSize = baseGrid.columnWidth + root.columnSpacing

            root.selectedPanel._model.column = Math.round(newX / tmpHSize)
            root.selectedPanel._model.row = Math.round(newY / tmpVSize)

            root.selectedPanel._model.columnSpan = Math.round(
                        (newWidth + root.columnSpacing) / tmpHSize)
            root.selectedPanel._model.rowSpan = Math.round(
                        (newHeight + root.rowSpacing) / tmpVSize)
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
