import QtQuick
import QtQuick.Layouts

import pd.mooody.me

Item {
    Component {
        id: unknownComponentErrorComponent
        PDLabel {
            property string componentType

            color: AppTheme.warn
            anchors.fill: parent
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            text: qsTr("Unknown Plugin Component") + "\n'" + componentType + "'"
        }
    }

    component GridPanel: PDGlowedRectangle {
        property var _model
        property int itemIndex
        property var itemProperties
        property var typeInfo: PanelModel.getQmlInfoFromType(_model.contentType)

        hoverEnabled: true

        x: baseGrid.spacedColumnWidth * _model.column
        y: baseGrid.spacedRowHeight * _model.row
        z: 10

        width: baseGrid.spacedColumnWidth * _model.columnSpan - root.columnSpacing
        height: baseGrid.spacedRowHeight * _model.rowSpan - root.rowSpacing

        Loader {
            id: _loader
            clip: true
            anchors.fill: parent
            anchors.margins: 10
            Component.onCompleted: {
                if (typeInfo.qmlPath === "") {
                    _loader.sourceComponent = unknownComponentErrorComponent
                    _loader.item.componentType = parent._model.contentType
                } else {
                    // Fix for "" being an invalid json
                    if (parent._model.contentData === "")
                        parent._model.contentData = "{}"

                    parent.itemProperties = JSON.parse(
                                parent._model.contentData)
                    if (Object.keys(parent.itemProperties).length === 0)
                        parent.itemProperties = typeInfo.initialProperties
                    updateQmlComponent(typeInfo.initialProperties)
                }
            }
        }

        function updateQmlComponent(initialProperties) {
            _loader.setSource(typeInfo.qmlPath, initialProperties)
            // TODO: Save Properties
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

    id: root
    property int totalRows: 30
    property int totalColumns: 30
    property int rowSpacing: 15
    property int columnSpacing: 15

    property bool editMode: false
    property GridPanel selectedPanel: null
    property bool itemMoving: false

    function syncSizeHandleSizes() {
        if (root.selectedPanel == null)
            return
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

        property real spacedRowHeight: baseGrid.rowHeight + root.rowSpacing
        property real spacedColumnWidth: baseGrid.columnWidth + root.columnSpacing

        Repeater {
            id: repeater
            model: PanelModel
            delegate: GridPanel {
                _model: model
                itemIndex: index
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
                        pluginPropertyEditor.setComponentProperties(
                                    root.selectedPanel.itemProperties)
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

            root.selectedPanel._model.column = Math.round(
                        newX / baseGrid.spacedColumnWidth)
            root.selectedPanel._model.row = Math.round(
                        newY / baseGrid.spacedRowHeight)

            root.selectedPanel._model.columnSpan = Math.round(
                        (newWidth + root.columnSpacing) / baseGrid.spacedColumnWidth)
            root.selectedPanel._model.rowSpan = Math.round(
                        (newHeight + root.rowSpacing) / baseGrid.spacedRowHeight)
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
        componentType: ""
    }
}
