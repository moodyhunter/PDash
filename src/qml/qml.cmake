list(APPEND QML_FILES
    ${CMAKE_CURRENT_LIST_DIR}/LoginPage.qml
    ${CMAKE_CURRENT_LIST_DIR}/MainComponent.qml
    ${CMAKE_CURRENT_LIST_DIR}/components/ActivityListView.qml
    ${CMAKE_CURRENT_LIST_DIR}/components/CircularButton.qml
    ${CMAKE_CURRENT_LIST_DIR}/components/PDPanelCard.qml
    ${CMAKE_CURRENT_LIST_DIR}/components/PanelGrid.qml
    ${CMAKE_CURRENT_LIST_DIR}/components/RectangleAreaHandle.qml
    )

foreach(qml ${QML_FILES})
    string(REPLACE "${CMAKE_CURRENT_LIST_DIR}/" "" qml_alias ${qml})
    set_source_files_properties(${qml} PROPERTIES QT_RESOURCE_ALIAS ${qml_alias})
endforeach(qml)

qt_add_qml_module(PD
    URI "pd.mooody.me"
    VERSION 1.0
    RESOURCE_PREFIX "/"
    QML_FILES
        ${QML_FILES}
)
