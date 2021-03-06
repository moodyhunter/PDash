install(TARGETS PDash RUNTIME DESTINATION .)

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

foreach(d ${DIRS})
    string(REPLACE "\\" "/" newd ${d})
    list(APPEND NEW_DIRS ${newd})
endforeach()
set(DIRS ${NEW_DIRS})

set(CMAKE_INSTALL_SYSTEM_RUNTIME_DESTINATION .)

set(APP "${CMAKE_INSTALL_PREFIX}/PDash.exe")
install(CODE "include(BundleUtilities)")
install(CODE "fixup_bundle(\"${APP}\"   \"\"   \"${DIRS}\")")
install(CODE "message(\"\")")
install(CODE "execute_process(COMMAND \"${Qt6_DIR}/../../../bin/windeployqt.exe\" \"${APP}\" --no-compiler-runtime --no-opengl-sw -qmldir=${CMAKE_CURRENT_SOURCE_DIR}/src/qml/ -qmlimport=.)")
install(CODE "message(\"Completed\")")
