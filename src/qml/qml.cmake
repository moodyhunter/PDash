list(APPEND QML_FILES
    ${CMAKE_CURRENT_LIST_DIR}/MainComponent.qml
    ${CMAKE_CURRENT_LIST_DIR}/controls/PDLabel.qml
    ${CMAKE_CURRENT_LIST_DIR}/controls/PDPanelCard.qml
    ${CMAKE_CURRENT_LIST_DIR}/controls/PDGlowedRectangle.qml
    ${CMAKE_CURRENT_LIST_DIR}/controls/CircularButton.qml
    ${CMAKE_CURRENT_LIST_DIR}/controls/RectangleAreaHandle.qml
    ${CMAKE_CURRENT_LIST_DIR}/views/ActivityListView.qml
    ${CMAKE_CURRENT_LIST_DIR}/views/GridPanelsView.qml
    ${CMAKE_CURRENT_LIST_DIR}/views/LoginView.qml
    ${CMAKE_CURRENT_LIST_DIR}/views/PluginTypeView.qml
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
