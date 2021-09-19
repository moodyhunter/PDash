# Qt network backend should be installed before copying the bundle.
install(DIRECTORY "${Qt6Core_DIR}/../../../plugins/tls/" DESTINATION "$<TARGET_BUNDLE_DIR:PDash>/Contents/PlugIns/tls/")

## Destination paths below are relative to ${CMAKE_INSTALL_PREFIX}
install(TARGETS PDash BUNDLE DESTINATION .)

# For Global Target
list(APPEND DIRS "${CMAKE_BINARY_DIR}")
list(APPEND DIRS "${CMAKE_CURRENT_BINARY_DIR}")
list(APPEND DIRS "${Qt6Core_DIR}/../../")
list(APPEND DIRS "${Qt6Core_DIR}/../../../bin/")

if(CMAKE_PREFIX_PATH)
    foreach(dir ${CMAKE_PREFIX_PATH})
        list(APPEND DIRS "${dir}/bin" "${dir}/lib")
    endforeach()
endif()

list(APPEND DIRS "${Qt6Core_DIR}/../..")
list(APPEND DIRS "/usr/lib")
list(APPEND DIRS "/usr/local/lib")

set(APP "${CMAKE_INSTALL_PREFIX}/PDash.app")
install(CODE "execute_process(COMMAND \"${Qt6_DIR}/../../../bin/macdeployqt\" \"${APP}\" -qmldir=${CMAKE_CURRENT_SOURCE_DIR}/src/qml/ -qmlimport=.)")
install(CODE "include(BundleUtilities)")
install(CODE "fixup_bundle(\"${APP}\"   \"\"   \"${DIRS}\")")
install(CODE "message(\"Run install_name_tool\")")
install(CODE "execute_process(COMMAND \"install_name_tool\" -add_rpath \"@executable_path/../Frameworks\" \"${APP}/Contents/MacOS/PDash\")")
install(CODE "message(\"Completed\")")
